#!/bin/sh
. /etc/sysconfig/wireless
. /etc/sysconfig/network

killall udhcpc
killall wpa_supplicant
ifconfig ${WLAN_DEVICE} down
sleep 1
rmmod 8723bs
# LED on lan connector on
i2cset -f -y 1 0x18 0x52 0
sleep 1

if [ "${NET_USE_DHCP}" == "Y" ]; then
	udhcpc -i ${NET_DEVICE} &
else
	ifconfig ${NET_DEVICE} ${NET_IP_ADDRESS} up
	route add default gw ${NET_GATEWAY}
fi
# Load anyway the 8723bs module
sleep 1
modprobe 8723bs

