#ifndef MUSICPOSITIONWIDGET_H
#define MUSICPOSITIONWIDGET_H

#include <QWidget>

#include "myslider.h"

class musicPositionWidget:public QWidget
{
public:
    musicPositionWidget(QWidget *parent);

private:
    void initWidget();
public:
    mySlider *m_mainslider;
protected:
    void mousePressEvent(QMouseEvent*);
};

#endif // MUSICPOSITIONWIDGET_H
