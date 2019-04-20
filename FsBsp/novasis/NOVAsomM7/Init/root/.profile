#
# .profile, started at boot from root user
# 
if [ -d /tmp/application_storage ]; then
        if [ -f /tmp/application_storage/AutoRun.sh ]; then
                chmod 777 /tmp/application_storage/AutoRun.sh
                /tmp/application_storage/AutoRun.sh &
        fi
fi
modprobe 8723bs
modprobe gpio-ir-recv

#for wayland
if [ -f /usr/bin/weston ]; then
	mkdir -p /tmp/.xdg &&  chmod 0700 /tmp/.xdg
	export XDG_RUNTIME_DIR=/tmp/.xdg
	weston --tty=2 --idle-time=0&
fi
