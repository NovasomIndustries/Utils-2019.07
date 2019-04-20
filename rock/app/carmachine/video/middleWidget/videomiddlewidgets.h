#ifndef VIDEOMIDDLEWIDGETS_H
#define VIDEOMIDDLEWIDGETS_H

#include "basewidget.h"
#include "videomiddlewidgetright.h"
#include "videomiddlewidgetleft.h"
#include <QStackedWidget>

class videoMiddleWidgets:public baseWidget
{
    Q_OBJECT
public:
    videoMiddleWidgets(QWidget *parent =0);

    QStackedWidget *m_stackWid;

    videoMiddleWidgetRight *m_rightWid;
    videoMiddleWidgetLeft *m_leftWid;

    void initLayout();

    bool isCurrentPlayMode(){return isOnPlayMode;}
public slots:
    void on_playMode();
    void on_ListMode();
private:
    bool isOnPlayMode;
};

#endif // VIDEOMIDDLEWIDGETS_H
