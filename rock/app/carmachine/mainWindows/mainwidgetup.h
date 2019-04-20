#ifndef MAINWIDGETUP_H
#define MAINWIDGETUP_H
#include "basewidget.h"
#include "basepushbutton.h"

#include <QLabel>
#include <QTimer>


class mainWidgetUp:public baseWidget
{
    Q_OBJECT
public:
    mainWidgetUp(QWidget *parent = 0);
public:
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;

    QLabel *m_lbltime;
//    QTimer *m_timer;  //  定时器，用于更新时间
private:
    void initLayout();
private slots:
    void slot_updatetime();

};

#endif // MAINWIDGETUP_H
