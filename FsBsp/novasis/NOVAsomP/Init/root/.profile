#
# .profile, started at boot from root user
# 
if [ -d /tmp/application_storage ]; then
        if [ -f /tmp/application_storage/AutoRun.sh ]; then
                chmod 777 /tmp/application_storage/AutoRun.sh
                /tmp/application_storage/AutoRun.sh &
        fi
fi
# for qt-web-kiosk
if [ -f /usr/bin/qt-webkit-kiosk ]; then
        RESOLUTION_WIDTH=`fbset | grep geometry | awk '{print $2}'`
        RESOLUTION_HEIGHT=`fbset | grep geometry | awk '{print $3}'`
        DEFAULT_ADDRESS="http:\/\/www.google.com"
        if [ -f /tmp/application_storage/default_address ]; then
                . /tmp/application_storage/default_address # this overwrites DEFAULT_ADDRESS
        fi
        cat /root/options.ini.TMPL | sed "s/DEFAULT_ADDRESS/$DEFAULT_ADDRESS/g" | sed "s/RESOLUTION_WIDTH/$RESOLUTION_WIDTH/g" | sed "s/RESOLUTION_HEIGHT/$RESOLUTION_HEIGHT/g" > /root/options.ini
fi

