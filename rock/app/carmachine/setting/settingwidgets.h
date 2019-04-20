#ifndef SETTINGWIDGETS_H
#define SETTINGWIDGETS_H

#include <basewidget.h>

#include "topWidget/settingtopwidgets.h"
#include "middleWidget/settingmiddlewidgets.h"


class settingWidgets:public baseWidget
{
public:
    settingWidgets(QWidget *parent = 0);

    settingTopWidgets *m_topWid;
    settingMiddleWidgets *m_middleWid;

private:
    void initLayout();

};

#endif // SETTINGWIDGETS_H
