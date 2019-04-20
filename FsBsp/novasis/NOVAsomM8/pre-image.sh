#!/bin/bash

echo "###### Customizing file system ######"
echo "cp -r board/novasis/NOVAsomM8/Init/* ${TARGET_DIR}"
cp -r board/novasis/NOVAsomM8/Init/* ${TARGET_DIR}
chmod 777 ${TARGET_DIR}/bin/*
chmod 777 ${TARGET_DIR}/etc/init.d/*
IP=`hostname -I | awk '{print $1}'`
echo "REFERENCE_SERVER=${IP}" > board/novasis/NOVAsomM8/Init/etc/sysconfig/system_vars
sync
exit $?
