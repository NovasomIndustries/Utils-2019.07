#ifndef UEVENTTHREAD_H
#define UEVENTTHREAD_H

#include <QThread>

class ueventThread:public QThread
{
public:
    ueventThread(QObject *parent=0);
protected:
    void run();
};

#endif // UEVENTTHREAD_H
