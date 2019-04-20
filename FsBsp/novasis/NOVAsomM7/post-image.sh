#!/bin/bash

echo "###### Creating $2 uInitrd for NOVAsomM7 ######"
output/host/usr/bin/mkimage -A arm -O linux -T ramdisk -C none -n "$2" -a 0x80000 -d output/images/rootfs.ext3.gz output/images/uInitrd
pushd ../../Deploy
rm uInitrd
ln -s ${BASE_DIR}/images/uInitrd
popd
exit $?
