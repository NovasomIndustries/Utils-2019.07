#include "inotifythread.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <QDirIterator>

#define EVENT_NUM 12
#include "global_value.h"

char *event_str[EVENT_NUM] =
{
    "IN_ACCESS",
    "IN_MODIFY",
    "IN_ATTRIB",
    "IN_CLOSE_WRITE",
    "IN_CLOSE_NOWRITE",
    "IN_OPEN",
    "IN_MOVED_FROM",
    "IN_MOVED_TO",
    "IN_CREATE",
    "IN_DELETE",
    "IN_DELETE_SELF",
    "IN_MOVE_SELF"
};

inotifyThread::inotifyThread(QObject *parent):QThread(parent)
{

}

void inotifyThread::run()
{
    int fd;
    int wd;
    int len;
    int nread;
    char buf[BUFSIZ];
    struct inotify_event *event;
    int i;

    fd = inotify_init();
    if( fd < 0 )
    {
        fprintf(stderr, "inotify_init failed\n");
        return;
    }


    QDirIterator it(MUSIC_SEARCH_PATH,QDir::Dirs);
    while (it.hasNext())
    {
        QString name = it.next();
        QFileInfo info(name);
        if (info.isDir())
        {
            inotify_add_watch(fd, info.absolutePath().toLatin1().data(),
                                       IN_CREATE | IN_DELETE | IN_DELETE_SELF);

        }
    }

    wd = inotify_add_watch(fd, MUSIC_SEARCH_PATH.toLatin1().data(),
                           IN_CREATE | IN_DELETE | IN_DELETE_SELF );

    buf[sizeof(buf) - 1] = 0;
    while( (len = read(fd, buf, sizeof(buf) - 1)) > 0 )
    {
        nread = 0;
        while( len > 0 )
        {
            event = (struct inotify_event *)&buf[nread];
            for(i=0; i<EVENT_NUM; i++)
            {
                if((event->mask >> i) & 1)
                {
                    if(event->len > 0)
                    {
//                        fprintf(stdout, "%s --- %s\n", event->name, event_str[i]);
                        if(mainwid!=NULL)
                        {
                            emit mainwid->beginUpdateMediaResource();
                        }
                    }
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}
