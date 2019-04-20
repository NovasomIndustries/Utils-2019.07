/*
 * Copyright 2017 Rockchip Electronics Co., Ltd
 *     Author: Jacob Chen <jacob2.chen@rock-chips.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */
#include "thread.h"
#include "common.h"
#include "v4l2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void* rkisp1_thread_entry(void* arg);

struct RKISP1Thread* RKISP1_3A_THREAD_CREATE(struct rkisp1_params* params)
{
    struct RKISP1Thread* rkisp1_thread;
    int err;

    if (params->mode == AAA_DISABLE_MODE)
        return NULL;

    rkisp1_thread = malloc(sizeof(struct RKISP1Thread));
    rkisp1_thread->rkisp1_core = malloc(sizeof(struct RKISP1Core));

    rkisp1_thread->mode = params->mode;
    rkisp1_thread->status = READY_STATUS;

    err = rkisp1_3a_core_init(rkisp1_thread->rkisp1_core, params);
    if (err) {
        printf("RKISP1: can't init rk-3a-core: %s\n", strerror(err));
        goto out;
    }

    pthread_mutex_init(&rkisp1_thread->mutex, NULL);
    pthread_mutex_init(&rkisp1_thread->result_mutex, NULL);
    err = pthread_create(&rkisp1_thread->tid, NULL, rkisp1_thread_entry, rkisp1_thread);
    if (err) {
        printf("RKISP1: can't create thread: %s\n", strerror(err));
        goto out;
    }

    return rkisp1_thread;

out:
    free(rkisp1_thread->rkisp1_core);
    free(rkisp1_thread);

    return NULL;
}

void RKISP1_3A_THREAD_EXIT(struct RKISP1Thread* rkisp1_thread)
{
    struct timeval start, now;

    if (!rkisp1_thread)
        return;

    RKISP1_3A_THREAD_STOP(rkisp1_thread);

    pthread_mutex_lock(&rkisp1_thread->mutex);
    rkisp1_thread->status = EXITING_STATUS;
    pthread_mutex_unlock(&rkisp1_thread->mutex);

    /* wait for exit */
    gettimeofday(&start, NULL);
    while (rkisp1_thread->status != EXITED_STATUS) {
        gettimeofday(&now, NULL);
        if (now.tv_sec - start.tv_sec > 2) {
            printf("RKISP1: Timed out waiting for thread to exit.\n");
            pthread_cancel(rkisp1_thread->tid);
            rkisp1_3a_core_deinit(rkisp1_thread->rkisp1_core);
            break;
        }
    }
    if (rkisp1_thread->status == EXITED_STATUS)
        pthread_join(rkisp1_thread->tid, NULL);

    free(rkisp1_thread->rkisp1_core);
    free(rkisp1_thread);
}

/* This function should be called before starting capture,
 * block until 3a core stream on.
 */
void RKISP1_3A_THREAD_START(struct RKISP1Thread* rkisp1_thread)
{
    if (!rkisp1_thread)
        return;

    if (rkisp1_thread->status != READY_STATUS)
        return;

    pthread_mutex_lock(&rkisp1_thread->mutex);
    rkisp1_thread->status = STARTING_STATUS;
    pthread_mutex_unlock(&rkisp1_thread->mutex);

    while (rkisp1_thread->status != RUN_STATUS)
        ;
}

/* This function should be called before stoping capture,
 * block until 3a core stream off.
 */
void RKISP1_3A_THREAD_STOP(struct RKISP1Thread* rkisp1_thread)
{
    struct timeval start, now;

    if (!rkisp1_thread)
        return;

    if (rkisp1_thread->status != RUN_STATUS)
        return;

    pthread_mutex_lock(&rkisp1_thread->mutex);
    rkisp1_thread->status = STOPING_STATUS;
    pthread_mutex_unlock(&rkisp1_thread->mutex);

    /* wait for stop */
    gettimeofday(&start, NULL);
    while (rkisp1_thread->status != READY_STATUS) {
        gettimeofday(&now, NULL);
        if (now.tv_sec - start.tv_sec > 2) {
            printf("RKISP1: Timed out waiting for thread to stop.\n");
            break;
        }
    }
}

void* rkisp1_thread_entry(void* arg)
{
    struct RKISP1Thread* rkisp1_thread = (struct RKISP1Thread*)arg;

    while (rkisp1_thread->status != EXITING_STATUS) {
        switch (rkisp1_thread->status) {
        case STARTING_STATUS:
            pthread_mutex_lock(&rkisp1_thread->mutex);
            /* stream off to flush buffer */
            rkisp1_3a_core_streamon(rkisp1_thread->rkisp1_core);
            rkisp1_thread->status = RUN_STATUS;
            pthread_mutex_unlock(&rkisp1_thread->mutex);
            break;
        case STOPING_STATUS:
            pthread_mutex_lock(&rkisp1_thread->mutex);
            /* stream off to flush buffer */
            rkisp1_3a_core_streamoff(rkisp1_thread->rkisp1_core);
            rkisp1_thread->status = READY_STATUS;
            pthread_mutex_unlock(&rkisp1_thread->mutex);
            break;
        case RUN_STATUS:
            if (rkisp1_3a_core_process_stats(rkisp1_thread->rkisp1_core))
                break;

            pthread_mutex_lock(&rkisp1_thread->result_mutex);
            rkisp1_3a_core_run_ae(rkisp1_thread->rkisp1_core);
            rkisp1_3a_core_run_awb(rkisp1_thread->rkisp1_core);
            rkisp1_3a_core_run_misc(rkisp1_thread->rkisp1_core);
            if (rkisp1_thread->mode == AAA_ENABLE_MODE)
                rkisp1_3a_core_run_af(rkisp1_thread->rkisp1_core);
            pthread_mutex_unlock(&rkisp1_thread->result_mutex);

            rkisp1_3a_core_process_params(rkisp1_thread->rkisp1_core);
            break;
        default:
            break;
        }
    }

    pthread_mutex_lock(&rkisp1_thread->mutex);
    rkisp1_thread->status = EXITED_STATUS;
    pthread_mutex_unlock(&rkisp1_thread->mutex);

    rkisp1_3a_core_deinit(rkisp1_thread->rkisp1_core);

    return NULL;
}

void RKISP1_GET_3A_RESULT(struct RKISP1Thread* rkisp1_thread, struct AiqResults* ret_result)
{
    if (ret_result == NULL)
        return;

    pthread_mutex_lock(&rkisp1_thread->result_mutex);
    *ret_result = rkisp1_thread->rkisp1_core->aiq_results;
    pthread_mutex_unlock(&rkisp1_thread->result_mutex);
}
