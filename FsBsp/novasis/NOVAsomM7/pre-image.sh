#!/bin/bash

echo "###### Customizing $2 file system ######"
echo "cp -r board/novasis/NOVAsomM7/Init/* ${TARGET_DIR}"
cp -r board/novasis/NOVAsomM7/Init/* ${TARGET_DIR}
chmod 777 ${TARGET_DIR}/bin/*
chmod 777 ${TARGET_DIR}/etc/init.d/*
sync
IP=`hostname -I | awk '{print $1}'`
echo "REFERENCE_SERVER=${IP}" > board/novasis/NOVAsomM7/Init/etc/sysconfig/system_vars
echo "FILE_SYSTEM_NAME=$2" > board/novasis/NOVAsomM7/Init/etc/sysconfig/filesystem_name
exit $?
