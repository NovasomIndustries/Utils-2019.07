#
# .profile, started at boot from root user
# 
if [ -d /tmp/application_storage ]; then
        if [ -f /tmp/application_storage/AutoRun.sh ]; then
                chmod 777 /tmp/application_storage/AutoRun.sh
                /tmp/application_storage/AutoRun.sh &
        fi
fi

