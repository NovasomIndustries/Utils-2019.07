#ifndef TOPWIDGETS_H
#define TOPWIDGETS_H
#include <basewidget.h>
#include "basepushbutton.h"


class topWidgets:public baseWidget
{
public:
    topWidgets(QWidget *parent = 0);

    FourStateButton *m_btnreturn;
    flatButton *m_btnicon;
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;
private:
    void initWidget();
};

#endif // TOPWIDGETS_H
