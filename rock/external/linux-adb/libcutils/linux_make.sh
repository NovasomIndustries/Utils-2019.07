#! /bin/sh

gcc -g -rdynamic -ldl -funwind-tables -fPIC -DANDROID_SMP=1 -DHAVE_PTHREADS -DHAVE_SYS_SOCKET_H -shared -o libcutils.so \
	hashmap.c \
	atomic.c \
	native_handle.c \
	socket_inaddr_any_server.c \
	socket_local_client.c \
	socket_local_server.c \
	socket_loopback_client.c \
	socket_loopback_server.c \
	socket_network_client.c \
	sockets.c \
	config_utils.c \
	cpu_info.c \
	load_file.c \
	list.c \
	open_memstream.c \
	strdup16to8.c \
	strdup8to16.c \
	record_stream.c \
	process_name.c \
	threads.c \
	sched_policy.c \
	iosched_policy.c \
	str_parms.c \
	ashmem-dev.c \
	debugger.c \
	klog.c \
	partition_utils.c \
	properties.c \
	qtaguid.c \
	trace.c \
	uevent.c \
	arch-arm/memset32.S \
	str.c \
	-I$(pwd) -lpthread


SYSTEMDIR=/usr/lib/arm-linux-gnueabihf/
SYSTEMINCDIR=/usr/include/

BUILDDIR=$(pwd)
BUILDBINARY=$BUILDDIR/libcutils.so
BUILDINCIDR="$BUILDDIR/cutils linux"

cp $BUILDBINARY $SYSTEMDIR
cp -r $BUILDINCIDR $SYSTEMINCDIR

