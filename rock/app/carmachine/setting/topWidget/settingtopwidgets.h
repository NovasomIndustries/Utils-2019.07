#ifndef SETTINGTOPWIDGETS_H
#define SETTINGTOPWIDGETS_H

#include "basewidget.h"
#include "basepushbutton.h"

class settingTopWidgets:public baseWidget
{
public:
    settingTopWidgets(QWidget *parent=0);

    FourStateButton *m_btnreturn;
    flatButton *m_btnicon;
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;
private:
    void initWidget();
};

#endif // SETTINGTOPWIDGETS_H
