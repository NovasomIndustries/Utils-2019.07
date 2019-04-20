#ifndef MIDDLEWIDGETRIGHT_H
#define MIDDLEWIDGETRIGHT_H
#include "basewidget.h"

#include "QLabel"


class middleWidgetRight:public baseWidget
{
public:
    middleWidgetRight(QWidget *parent =0);
private:
    QLabel *m_lblTip;

    void initLayout();
};

#endif // MIDDLEWIDGETRIGHT_H
