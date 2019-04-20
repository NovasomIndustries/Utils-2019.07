################################################################################
#
# rtl8723bs
#
################################################################################

RTL8723BS_BT_VERSION = 51baf5b0eb4d3c4f0e04a03835087ffd2c6c8e2e
RTL8723BS_BT_SITE = $(call github,Novasomindustries,rtl8723bs_bt,HEAD)
RTL8723BS_BT_LICENSE = LGPL-2.1+

define RTL8723BS_BT_BUILD_CMDS
        $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define RTL8723BS_BT_INSTALL_TARGET_CMDS
        $(INSTALL) -m 0755 -D $(@D)/rtk_hciattach $(TARGET_DIR)/usr/bin/rtk_hciattach
	$(INSTALL) -m 0755 -D $(@D)/go_bt.sh $(TARGET_DIR)/bin/go_bt.sh
	$(INSTALL) -m 0755 -D $(@D)/setup_wifi.sh $(TARGET_DIR)/bin/setup_wifi.sh
	$(INSTALL) -m 0755 -D $(@D)/start_bt.sh $(TARGET_DIR)/bin/start_bt.sh
endef

$(eval $(generic-package))
