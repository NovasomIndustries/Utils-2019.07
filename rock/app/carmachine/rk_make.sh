#! /bin/bash

TOP_DIR=$(pwd)
BUILDROOT_TARGET_PATH=$(pwd)/../../buildroot/output/target/
QMAKE=$(pwd)/../../buildroot/output/host/bin/qmake
PRODUCT_NAME=`ls ../../device/rockchip/`

#Carmachine have to build different version base on the dpi of hardware board,
#we have 2 hardware evb board: rk3399 evb board and px3se evb board,they have different
#dpi,if we build px3se firmware, we should disable the macro DEFINES += DEVICE_EVB
#to build a low dpi app,otherwise we build high dpi app based on rk3399 board.
if [ "$PRODUCT_NAME"x = "px3-se"x ];then
sed -i '/DEVICE_EVB/s/^/#&/' Carmachine.pro
fi

#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
        mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
        make clean
elif [ "$1" = "distclean" ];then
        make clean
else
	mulcore_cmd=-j4
fi

#qmake and build target
$QMAKE
make $mulcore_cmd
check_err_exit $?

cp $TOP_DIR/Carmachine $BUILDROOT_TARGET_PATH/usr/bin/
make clean
echo "Carmachine app is ready."

#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
        make clean
fi

#we should restore the modifcation which is made on this script above.
if [ "$PRODUCT_NAME"x = "px3-se"x ];then
sed -i '/DEVICE_EVB/s/^.//' Carmachine.pro
fi
