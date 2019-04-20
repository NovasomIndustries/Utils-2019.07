#! /bin/sh

gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o adbd \
		adb.c \
		backup_service.c \
		fdevent.c \
		transport.c \
		transport_local.c \
		transport_usb.c \
		adb_auth_client.c \
		sockets.c services.c \
		file_sync_service.c \
		jdwp_service.c \
		remount_service.c \
		usb_linux_client.c \
		mincrypt/rsa.c \
		mincrypt/sha256.c \
		mincrypt/sha.c \
		-I$(pwd) -lpthread -lcutils 

SYSTEMDIR=/usr/local/sbin

BUILDDIR=$(pwd)
BUILDBINARY=$BUILDDIR/adbd

cp $BUILDBINARY $SYSTEMDIR

