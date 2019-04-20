/* GStreamer
 *
 * Copyright (C) 2002 Ronald Bultje <rbultje@ronald.bitfreak.net>
 *               2006 Edgard Lima <edgard.lima@gmail.com>
 *
 * v4l2_calls.h - generic V4L2 calls handling
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
 */

#ifndef __V4L2_CALLS_H__
#define __V4L2_CALLS_H__

#include "gstv4l2object.h"

#undef HAVE_LIBV4L2

#ifdef HAVE_LIBV4L2
#  include <libv4l2.h>
#else
#  include "ext/videodev2.h"
#  include <sys/ioctl.h>
#  include <sys/mman.h>
#  include <unistd.h>
#  define v4l2_fd_open(fd, flags) (fd)
#  define v4l2_close    close
#  define v4l2_dup      dup
#  define v4l2_ioctl    ioctl
#  define v4l2_read     read
#  define v4l2_mmap     mmap
#  define v4l2_munmap   munmap
#endif

#define GST_V4L2_IS_OVERLAY(v4l2object) \
  (v4l2object->vcap.capabilities & V4L2_CAP_VIDEO_OVERLAY)

/* checks whether the current v4lv4l2object has already been open()'ed or not */
#define GST_V4L2_CHECK_OPEN(v4l2object)				\
  if (!GST_V4L2_IS_OPEN(v4l2object))				\
  {								\
    GST_ELEMENT_ERROR (v4l2object->element, RESOURCE, SETTINGS,	\
      (_("Device is not open.")), (NULL));                      \
    return FALSE;						\
  }

/* checks whether the current v4lv4l2object is close()'ed or whether it is still open */
#define GST_V4L2_CHECK_NOT_OPEN(v4l2object)			\
  if (GST_V4L2_IS_OPEN(v4l2object))				\
  {								\
    GST_ELEMENT_ERROR (v4l2object->element, RESOURCE, SETTINGS,	\
      (_("Device is open.")), (NULL));                          \
    return FALSE;						\
  }

/* checks whether the current v4lv4l2object does video overlay */
#define GST_V4L2_CHECK_OVERLAY(v4l2object)			\
  if (!GST_V4L2_IS_OVERLAY(v4l2object))				\
  {								\
    GST_ELEMENT_ERROR (v4l2object->element, RESOURCE, SETTINGS, \
      (NULL), ("Device cannot handle overlay"));                \
    return FALSE;						\
  }

/* checks whether we're in capture mode or not */
#define GST_V4L2_CHECK_ACTIVE(v4l2object)			\
  if (!GST_V4L2_IS_ACTIVE(v4l2object))				\
  {								\
    GST_ELEMENT_ERROR (v4l2object->element, RESOURCE, SETTINGS, \
      (NULL), ("Device is not in streaming mode"));             \
    return FALSE;						\
  }

/* checks whether we're out of capture mode or not */
#define GST_V4L2_CHECK_NOT_ACTIVE(v4l2object)			\
  if (GST_V4L2_IS_ACTIVE(v4l2object))				\
  {								\
    GST_ELEMENT_ERROR (v4l2object->element, RESOURCE, SETTINGS, \
      (NULL), ("Device is in streaming mode"));                 \
    return FALSE;						\
  }

/* open/close the device */
gboolean gst_v4l2_open (GstRKV4l2Object * v4l2object);
gboolean gst_v4l2_dup (GstRKV4l2Object * v4l2object, GstRKV4l2Object * other);
gboolean gst_v4l2_close (GstRKV4l2Object * v4l2object);

/* input/output */
gboolean gst_v4l2_get_input (GstRKV4l2Object * v4l2object, gint * input);
gboolean gst_v4l2_set_input (GstRKV4l2Object * v4l2object, gint input);
gboolean gst_v4l2_get_output (GstRKV4l2Object * v4l2object, gint * output);
gboolean gst_v4l2_set_output (GstRKV4l2Object * v4l2object, gint output);

/* attribute control */
gboolean gst_v4l2_get_attribute (GstRKV4l2Object * v4l2object,
    int attribute, int *value);
gboolean gst_v4l2_set_attribute (GstRKV4l2Object * v4l2object,
    int attribute, const int value);

gboolean gst_v4l2_set_controls (GstRKV4l2Object * v4l2object,
    GstStructure * controls);

gboolean gst_v4l2_get_capabilities (GstRKV4l2Object * v4l2object);


#endif /* __V4L2_CALLS_H__ */
