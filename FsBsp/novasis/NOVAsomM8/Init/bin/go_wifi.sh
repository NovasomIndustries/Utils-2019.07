#!/bin/sh
. /etc/sysconfig/wireless
ifconfig eth0 down
killall udhcpc
if [ "$1" = "" ]; then
	wpa_supplicant -i$WLAN_DEVICE -c/etc/wpa_supplicant.conf &
else
	wpa_supplicant -i$WLAN_DEVICE -c/etc/wpa_supplicant.conf -D$1 &
fi
if [ "$WLAN_USE_DHCP" == "Y" ]; then
	udhcpc -i $WLAN_DEVICE &
else
	ifconfig $WLAN_DEVICE $WLAN_IP_ADDRESS up
	route add default gw $WLAN_GATEWAY
fi

