#!/bin/sh
MINILOADER="rock_bin_files/rk3328_miniloader_v2.43.bin"
DDR="rock_bin_files/rk3328_ddr_333MHz_v1.13.bin"
BOOTDIR="../../Bootloader/u-boot-novasomM7-2017.09"


${BOOTDIR}/tools/mkimage -n rk3328 -T rksd -d ${DDR} idbloader.img -v
cat ${MINILOADER} >> idbloader.img
