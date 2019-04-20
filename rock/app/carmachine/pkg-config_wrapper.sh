#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/home/fil/linux/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/home/fil/linux/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/pkgconfig:/home/fil/linux/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/share/pkgconfig:/home/fil/linux/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/aarch64-buildroot-linux-gnu/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
