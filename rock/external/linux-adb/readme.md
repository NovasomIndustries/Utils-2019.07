# Build
Copy adb and libcutils to board  
```
cd libcutils
./linux_make.sh
cd ../
cd adb
./linux_make.sh
cd ../
```
Now adbd is installed in `/usr/local/sbin/`  

# Usage
run the following command In board and connect the board to the host computer:  
```
run_adbd.sh 
UDC=`ls /sys/class/udc/| awk '{print $1}'`
echo $UDC > /sys/kernel/config/usb_gadget/g1/UDC
```
run the following command in host:  
```
echo 0x2207> ~/.android/adb_usb.ini 
sudo adb shell
```
Notes:  
1. Make sure OTG port is enabled, try `ls /sys/class/udc/` to list.  