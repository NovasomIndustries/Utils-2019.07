GST1_LIBAV_RK_SITE = "https://github.com/JamesLinEngineer/gst-libav-rk.git"
GST1_LIBAV_RK_VERSION = 3.3
GST1_LIBAV_RK_SITE_METHOD = git
GST1_LIBAV_RK_GIT_SUBMODULES = YES

GST1_LIBAV_RK_LICENSE_FILES = COPYING
GST1_LIBAV_RK_LICENSE = GPLv2.1+
GST1_LIBAV_RK_AUTORECONF = YES
GST1_LIBAV_RK_DEPENDENCIES = gst1-plugins-base libdrm


ifeq ($(BR2_PACKAGE_GST1_LIBAV_RK_COLMV),y)
GST1_LIBAV_RK_CONF_ENV = \
        CFLAGS="$(TARGET_CFLAGS) \
                -DUSE_4K_COLMV=1"
endif

ifeq ($(BR2_PACKAGE_GST1_LIBAV_RK_DROP_ERROR),y)
GST1_LIBAV_RK_CONF_ENV = \
	CFLAGS="$(TARGET_CFLAGS) \
               -DDROP_ERROR_FRAME=1"
endif

ifeq ($(BR2_PACKAGE_GST1_LIBAV_RK_LOW_MEMORY),y)
GST1_LIBAV_RK_CONF_ENV = \
	CFLAGS="$(TARGET_CFLAGS) \
               -DLOW_MEMORY=1"
endif
CC="$(TARGET_CC)"
GST1_LIBAV_RK_CONF_OPTS = \
 	--target=aarch64-linux --host=aarch64-linux \
	--enable-hwaccel=hevc_rkvdec --enable-hwaccel=hevc_rkvdec10 \
	--enable-hwaccel=h264_rkvdec --enable-hwaccel=vp8_rkvdec --enable-hwaccel=vp9_rkvdec \
	--enable-hwaccel=h263_rkvdec --enable-hwaccel=mpeg2video_rkvdec --enable-hwaccel=mpeg4_rkvdec

$(eval $(autotools-package))
