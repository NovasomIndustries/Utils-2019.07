#!/bin/sh
echo 0 > /sys/class/rfkill/rfkill0/state
sleep 1
echo 1 > /sys/class/rfkill/rfkill0/state
sleep 1
/usr/bin/rtk_hciattach -n -s 115200 ttyS0 rtk_h5 > /tmp/hciattach.txt 2>&1 &
sleep 5
/usr/bin/hciconfig -a >> /tmp/hciattach.txt
/usr/bin/hciconfig hci0 up
/usr/bin/hcitool scan > /tmp/bt_scan.txt

