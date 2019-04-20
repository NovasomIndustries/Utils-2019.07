/* GStreamer
 *
 * Copyright (C) 2001-2002 Ronald Bultje <rbultje@ronald.bitfreak.net>
 *               2006 Edgard Lima <edgard.lima@gmail.com>
 *
 * GstRKV4l2Object.h: base class for V4L2 elements
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

#ifndef __GST_V4L2_OBJECT_H__
#define __GST_V4L2_OBJECT_H__

#include "common.h"

#include "ext/videodev2.h"
#include "v4l2-utils.h"

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>

#include <gst/video/video.h>

typedef struct _GstV4l2Object GstRKV4l2Object;
typedef struct _GstV4l2ObjectClassHelper GstRKV4l2ObjectClassHelper;
typedef struct _GstV4l2Xv GstRKV4l2Xv;

#include <gstv4l2bufferpool.h>

/* size of v4l2 buffer pool in streaming case */
#define GST_V4L2_MIN_BUFFERS 2

/* max frame width/height */
#define GST_V4L2_MAX_SIZE (1<<15)       /* 2^15 == 32768 */

G_BEGIN_DECLS
#define GST_TYPE_V4L2_IO_MODE (gst_v4l2_io_mode_get_type ())
    GType gst_v4l2_io_mode_get_type (void);

#define GST_V4L2_OBJECT(obj) (GstRKV4l2Object *)(obj)

typedef enum
{
  GST_V4L2_IO_AUTO = 0,
  GST_V4L2_IO_RW = 1,
  GST_V4L2_IO_MMAP = 2,
  GST_V4L2_IO_USERPTR = 3,
  GST_V4L2_IO_DMABUF = 4,
  GST_V4L2_IO_DMABUF_IMPORT = 5
} GstV4l2IOMode;

typedef gboolean (*GstV4l2GetInOutFunction) (GstRKV4l2Object * v4l2object,
    gint * input);
typedef gboolean (*GstV4l2SetInOutFunction) (GstRKV4l2Object * v4l2object,
    gint input);
typedef gboolean (*GstV4l2UpdateFpsFunction) (GstRKV4l2Object * v4l2object);

#define GST_V4L2_WIDTH(o)        (GST_VIDEO_INFO_WIDTH (&(o)->info))
#define GST_V4L2_HEIGHT(o)       (GST_VIDEO_INFO_HEIGHT (&(o)->info))
#define GST_V4L2_PIXELFORMAT(o)  ((o)->fmtdesc->pixelformat)
#define GST_V4L2_FPS_N(o)        (GST_VIDEO_INFO_FPS_N (&(o)->info))
#define GST_V4L2_FPS_D(o)        (GST_VIDEO_INFO_FPS_D (&(o)->info))

/* simple check whether the device is open */
#define GST_V4L2_IS_OPEN(o)      ((o)->video_fd > 0)

/* check whether the device is 'active' */
#define GST_V4L2_IS_ACTIVE(o)    ((o)->active)
#define GST_V4L2_SET_ACTIVE(o)   ((o)->active = TRUE)
#define GST_V4L2_SET_INACTIVE(o) ((o)->active = FALSE)

struct _GstV4l2Object
{
  GstElement *element;

  enum v4l2_buf_type type;      /* V4L2_BUF_TYPE_VIDEO_CAPTURE, V4L2_BUF_TYPE_VIDEO_OUTPUT */

  /* the video device */
  char *videodev;

  /* the video-device's file descriptor */
  gint video_fd;
  GstV4l2IOMode mode;

  gboolean active;
  gboolean streaming;

  /* the current format */
  struct v4l2_fmtdesc *fmtdesc;
  struct v4l2_format format;
  GstVideoInfo info;
  GstVideoAlignment align;

  /* Features */
  gboolean need_video_meta;
  gboolean has_alpha_component;

  /* only used if the device supports MPLANE
   * nb planes is meaning of v4l2 planes
   * the gstreamer equivalent is gst_buffer_n_memory
   */
  gint n_v4l2_planes;

  /* We cache the frame duration if known */
  GstClockTime duration;

  /* if the MPLANE device support both contiguous and non contiguous
   * it allows to select which one we want. But we prefered_non_contiguous
   * non contiguous mode.
   */
  gboolean prefered_non_contiguous;

  /* This will be set if supported in decide_allocation. It can be used to
   * calculate the minimum latency. */
  guint32 min_buffers;

  /* This will be set if supported in propose allocation. */
  guint32 min_buffers_for_output;

  /* wanted mode */
  GstV4l2IOMode req_mode;

  /* optional pool */
  GstBufferPool *pool;

  /* the video device's capabilities */
  struct v4l2_capability vcap;
  /* opened device specific capabilities */
  guint32 device_caps;

  /* the video device's window properties */
  struct v4l2_window vwin;

  /* some more info about the current input's capabilities */
  struct v4l2_input vinput;

  /* lists... */
  GSList *formats;              /* list of available capture formats */
  GstCaps *probed_caps;

  GList *colors;
  //GList *channels;
  GData *controls;

  /* properties */
  GstStructure *extra_controls;
  gboolean keep_aspect;
  GValue *par;

  /* X-overlay */
  GstRKV4l2Xv *xv;
  gulong xwindow_id;

  /* funcs */
  GstV4l2GetInOutFunction get_in_out_func;
  GstV4l2SetInOutFunction set_in_out_func;
  GstV4l2UpdateFpsFunction update_fps_func;

  /* Quirks */
  /* Skips interlacing probes */
  gboolean never_interlaced;
  /* Allow to skip reading initial format through G_FMT. Some devices
   * just fails if you don't call S_FMT first. (ex: M2M decoders) */
  gboolean no_initial_format;

  RK_V4L2_OBJECT
};

struct _GstV4l2ObjectClassHelper
{
  /* probed devices */
  GList *devices;
};

GType gst_v4l2_object_get_type (void);

#define V4L2_STD_OBJECT_PROPS \
    PROP_DEVICE,              \
    PROP_DEVICE_NAME,         \
    PROP_DEVICE_FD,           \
    PROP_FLAGS,               \
    PROP_BRIGHTNESS,          \
    PROP_CONTRAST,            \
    PROP_SATURATION,          \
    PROP_HUE,                 \
    PROP_TV_NORM,             \
    PROP_IO_MODE,             \
    PROP_OUTPUT_IO_MODE,      \
    PROP_CAPTURE_IO_MODE,     \
    PROP_EXTRA_CONTROLS,      \
    PROP_PIXEL_ASPECT_RATIO,  \
    PROP_FORCE_ASPECT_RATIO, \
    RK_V4L2_OBJECT_PROPS

/* create/destroy */
GstRKV4l2Object *gst_v4l2_object_new (GstElement * element,
    enum v4l2_buf_type type,
    const char *default_device,
    GstV4l2GetInOutFunction get_in_out_func,
    GstV4l2SetInOutFunction set_in_out_func,
    GstV4l2UpdateFpsFunction update_fps_func);

void gst_v4l2_object_destroy (GstRKV4l2Object * v4l2object);

/* properties */

void gst_v4l2_object_install_properties_helper (GObjectClass * gobject_class,
    const char *default_device);

void gst_v4l2_object_install_m2m_properties_helper (GObjectClass *
    gobject_class);

void gst_v4l2_object_install_rockchip_properties_helper (GObjectClass *
    gobject_class);

gboolean gst_v4l2_object_set_property_helper (GstRKV4l2Object * v4l2object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
gboolean gst_v4l2_object_get_property_helper (GstRKV4l2Object * v4l2object,
    guint prop_id, GValue * value, GParamSpec * pspec);
/* open/close */
gboolean gst_v4l2_object_open (GstRKV4l2Object * v4l2object);
gboolean gst_v4l2_object_open_shared (GstRKV4l2Object * v4l2object,
    GstRKV4l2Object * other);
gboolean gst_v4l2_object_close (GstRKV4l2Object * v4l2object);

/* probing */

GstCaps *gst_v4l2_object_get_all_caps (void);

GstCaps *gst_v4l2_object_get_raw_caps (void);

GstCaps *gst_v4l2_object_get_codec_caps (void);

gint gst_v4l2_object_extrapolate_stride (const GstVideoFormatInfo * finfo,
    gint plane, gint stride);

gboolean gst_v4l2_object_set_format (GstRKV4l2Object * v4l2object, GstCaps * caps,
    GstV4l2Error * error);
gboolean gst_v4l2_object_try_format (GstRKV4l2Object * v4l2object, GstCaps * caps,
    GstV4l2Error * error);

gboolean gst_v4l2_object_caps_equal (GstRKV4l2Object * v4l2object,
    GstCaps * caps);

gboolean gst_v4l2_object_unlock (GstRKV4l2Object * v4l2object);
gboolean gst_v4l2_object_unlock_stop (GstRKV4l2Object * v4l2object);

gboolean gst_v4l2_object_stop (GstRKV4l2Object * v4l2object);

GstCaps *gst_v4l2_object_probe_caps (GstRKV4l2Object * v4l2object,
    GstCaps * filter);
GstCaps *gst_v4l2_object_get_caps (GstRKV4l2Object * v4l2object,
    GstCaps * filter);

gboolean gst_v4l2_object_acquire_format (GstRKV4l2Object * v4l2object,
    GstVideoInfo * info);

gboolean gst_v4l2_object_set_crop (GstRKV4l2Object * obj);

gboolean gst_v4l2_object_decide_allocation (GstRKV4l2Object * v4l2object,
    GstQuery * query);

gboolean gst_v4l2_object_propose_allocation (GstRKV4l2Object * obj,
    GstQuery * query);

GstStructure *gst_v4l2_object_v4l2fourcc_to_structure (guint32 fourcc);

G_END_DECLS
#endif /* __GST_V4L2_OBJECT_H__ */
