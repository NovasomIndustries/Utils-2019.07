#ifndef MUSICGROUPWIDGET_H
#define MUSICGROUPWIDGET_H
#include <QObject>
#include "basewidget.h"
#include "basepushbutton.h"


class musicItemGroupWidget:public baseWidget
{
public:
    musicItemGroupWidget(QWidget *parent = 0);
    flatButton *m_btnMovie;
    flatButton *m_btnLove;
    flatButton *m_btnDel;
    flatButton *m_btnMore;
    void setLoved();
    bool isLoved(){return m_islove;}
signals:

public slots:
    void slot_btnloveclicked();
private:
    bool m_islove;

};

#endif // MUSICGROUPWIDGET_H
