#include "hdmithread.h"

//#include "global_value.h"
//#include <errno.h>
//#include <fcntl.h>
//#include <pthread.h>
//#include <signal.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <string.h>

//#include <linux/netlink.h>
//#include <sys/socket.h>
//#include <sys/time.h>

//struct _uevent {
//    char *strs[30];
//    int size;
//};

//static void uevent_display_handler(const struct _uevent *event)
//{
//    const char itf_type[] = "INTERFACE=";
//    char *tmp = NULL;
//    char *act = event->strs[0] + 7;
//    int i;

//    for (i = 3; i < event->size; i++) {
//        tmp = event->strs[i];
//        /* search "INTERFACE=" */
//        if (!strncmp(itf_type, tmp, strlen(itf_type)))
//            break;
//    }

//    if (i < event->size) {
//        tmp = strchr(tmp, '=') + 1;
//        if (!strncmp(tmp, "HDMI", strlen(tmp))) {
//            if (!strcmp(act, "add")) {
//                qDebug()<<"******HDMI ADD*******";
//                printf("HDMI ADD\n");

//                //rk_fb_set_out_device(OUT_DEVICE_HDMI);
//                //rk_fb_ui_config(g_fb);
//            } else {
//                qDebug()<<"******HDMI MOVE*******";
//                printf("HDMI MOVE\n");
//                //rk_fb_set_out_device(OUT_DEVICE_LCD);
//                //rk_fb_ui_config(g_fb);
//            }
//        }
//    }
//}

//static void parse_event(const struct _uevent *event)
//{
//    char *tmp = NULL;
//    char *sysfs = NULL;
//    if (event->size <= 0)
//        return;

//    sysfs = event->strs[2] + 10;
//    if (!strcmp(sysfs, "display"))
//        uevent_display_handler(event);
//}

//static int uevent_monitor_run(void)
//{
//    int sockfd;
//    int i, j, len;
//    char buf[512];
//    struct iovec iov;
//    struct msghdr msg;
//    struct sockaddr_nl sa;
//    struct _uevent event;

//    memset(&sa, 0, sizeof(sa));
//    sa.nl_family = AF_NETLINK;
//    sa.nl_groups = NETLINK_KOBJECT_UEVENT;
//    sa.nl_pid = 0;

//    memset(&msg, 0, sizeof(msg));
//    msg.msg_name = (void *)&sa;
//    msg.msg_namelen = sizeof(sa);
//    msg.msg_iov = &iov;
//    msg.msg_iovlen = 1;

//    memset(&iov, 0, sizeof(iov));
//    iov.iov_base = (void *)buf;
//    iov.iov_len = sizeof(buf);

//    sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
//    if (sockfd < 0) {
//        printf("socket creating failed: %s\n", strerror(errno));
//        return -1;
//   }

//    if (bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
//        printf("bind error: %s\n", strerror(errno));
//       // close(sockfd);
//        return -1;
//    }

//    while (1) {
//        event.size = 0;
//        len = recvmsg(sockfd, &msg, 0);

//        if (len < 0) {
//            printf("receive error\n");
//        } else if (len < 32 || len > sizeof(buf)) {
//            printf("invalid message");
//        } else {
//            for (i = 0, j = 0; i < len; i++) {
//                if (*(buf + i) == '\0' && (i + 1) != len) {
//                    event.strs[j++] = buf + i + 1;
//                    event.size = j;
//                }
//            }
//        }
//        parse_event(&event);
//    }
//}



hdmiThread::hdmiThread(QObject *parent):QThread(parent)
{
}

void hdmiThread::run()
{
//    uevent_monitor_run();
}
