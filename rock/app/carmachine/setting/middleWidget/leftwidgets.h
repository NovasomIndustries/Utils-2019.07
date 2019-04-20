#ifndef LEFTWIDGETS_H
#define LEFTWIDGETS_H

#include "basewidget.h"
#include "funtiontablewidget.h"

class leftWidgets:public baseWidget
{
public:
    leftWidgets(QWidget *parent=0);

    funtiontablewidget *m_funtionlist;
private:
    void initLayout();
};

#endif // LEFTWIDGETS_H
