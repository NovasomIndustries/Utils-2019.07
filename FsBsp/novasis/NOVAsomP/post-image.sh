#!/bin/bash

echo "###### Creating uInitrd for NOVAsomP ######"
output/host/usr/bin/mkimage -A arm -O linux -T ramdisk -C none -n "NOVAsomP" -a 0x80000 -d output/images/rootfs.ext3.gz output/images/uInitrd
pushd ../../Deploy
rm uInitrd
ln -s ${BASE_DIR}/images/uInitrd
popd
exit $?
