DRM_HELPER_SITE = $(TOPDIR)/../../Utils/rock/external/drm_helper
DRM_HELPER_SITE_METHOD = local
DRM_HELPER_INSTALL_STAGING = YES

DRM_HELPER_DEPENDENCIES += libdrm

ifeq ($(BR2_PACKAGE_DRM_HELPER_DISPLAY),y)
DRM_HELPER_DEPENDENCIES += linux-rga
endif

DRM_HELPER_CONF_OPTS += "-DDOT_GIT_PARENT_DIR=$($(PKG)_SITE)" \
						"-DMODULE_ALLOCATOR=$(if $(BR2_PACKAGE_DRM_HELPER_ALLOCATOR),ON,OFF)" \
						"-DMODULE_DISPLAY=$(if $(BR2_PACKAGE_DRM_HELPER_DISPLAY),ON,OFF)"

$(eval $(cmake-package))