#ifndef HDMITHREAD_H
#define HDMITHREAD_H

#include <QThread>

class hdmiThread:public QThread
{
    Q_OBJECT
public:
    hdmiThread(QObject *parent = 0);
    void run();
};

#endif // HDMITHREAD_H
