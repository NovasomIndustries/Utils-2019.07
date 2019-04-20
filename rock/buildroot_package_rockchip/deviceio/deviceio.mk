DEVICEIO_SITE = $(TOPDIR)/../../Utils/rock/external/deviceio
DEVICEIO_SITE_METHOD = local
DEVICEIO_INSTALL_STAGING = YES

ifeq ($(BR2_PACKAGE_BLUEZ5_UTILS),y)
DEVICEIO_CONF_OPTS += -DBLUEZ5_UTILS=TRUE
DEVICEIO_DEPENDENCIES += bluez5_utils libglib2
endif
DEVICEIO_CONF_OPTS += -DCPU_ARCH=$(BR2_ARCH)

DEVICEIO_DEPENDENCIES += wpa_supplicant alsa-lib

$(eval $(cmake-package))


