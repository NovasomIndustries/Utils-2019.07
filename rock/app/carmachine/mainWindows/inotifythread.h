#ifndef INOTIFYTHREAD_H
#define INOTIFYTHREAD_H

#include <QThread>

class inotifyThread:public QThread
{
public:
    inotifyThread(QObject *parent=0);
protected:
    void run();
};

#endif // INOTIFYTHREAD_H
