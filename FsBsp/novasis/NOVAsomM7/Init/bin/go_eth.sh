#!/bin/sh
. /etc/sysconfig/wireless
. /etc/sysconfig/network

killall udhcpc
killall wpa_supplicant
ifconfig ${WLAN_DEVICE} down
rmmod 8723bs
# LED on lan connector on
i2cset -f -y 1 0x18 0x52 0
sleep 1

Use the code below for a static ip wifi address
if [ "${NET_USE_DHCP}" == "Y" ]; then
	udhcpc -i ${NET_DEVICE} &
else
	ifconfig ${NET_DEVICE} ${NET_IP_ADDRESS} up
	route add default gw ${NET_GATEWAY}
fi
modprobe 8723bs

