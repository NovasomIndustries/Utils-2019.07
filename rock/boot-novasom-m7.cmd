setenv load_addr "0x39000000"
# default values
setenv rootdev "/dev/ram"
setenv fdtfile "dtb.dtb"
setenv consoleargs "console=ttyFIQ0,115200"
setenv bootdev "mmc 1:1"

echo "NOVAsom M7 Boot script loaded from ${devtype} ${devnum}"

setenv bootargs "root=${rootdev} rootwait ramdisk_size=512000 ${consoleargs} consoleblank=0"

load ${bootdev} ${ramdisk_addr_r} uInitrd
load ${bootdev} ${kernel_addr_r} Image
load ${bootdev} ${fdt_addr_r} ${fdtfile}
booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}

# Recompile with:
# mkimage -C none -A arm -T script -d boot-novasom-m7.cmd boot.scr

