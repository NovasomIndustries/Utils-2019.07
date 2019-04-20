#!/bin/sh
DISK="/dev/mmcblk2"
FILES="m7-idbloader.img m7-uboot.img m7-trust.img m7_dtb.dtb m7_Image uInitrd NOVAsomParams"
for i in ${FILES}; do
	get_exec ${i}
done

cd /tmp
for i in ${FILES}; do
	if ! [ -f ${i} ]; then
		echo "${i} is missing. Givin' up"
		exit
	fi
done

dd if=m7-idbloader.img of=${DISK} seek=64 conv=notrunc
dd if=m7-uboot.img of=${DISK} seek=16384 conv=notrunc
dd if=m7-trust.img of=${DISK} seek=24576 conv=notrunc

sgdisk -Z ${DISK} > /dev/null 2>&1
sudo partprobe ${DISK} > /dev/null 2>&1
echo "Done"
sync
echo -n "Creating partitions ... "
sgdisk -n 1::+7M  -c 1:loader1 ${DISK}  
sgdisk -n 2::+4M  -c 2:loader2 ${DISK}  
sgdisk -n 3::+4M  -c 3:trust ${DISK}  
sgdisk -n 8::+512M -c 8:M7Boot ${DISK}  
sgdisk -n 4::+16M -c 4:config ${DISK}  
partprobe ${DISK}
echo "y" | mkfs.ext4 ${DISK}p4
echo "y" | mkfs.ext4 ${DISK}p8
mount ${DISK}p8 /mnt
cp m7_Image /mnt/Image
cp m7_dtb.dtb /mnt/dtb.dtb
cp uInitrd /mnt/uInitrd
cp NOVAsomParams /mnt/NOVAsomParams
umount /mnt
sync

