#ifndef VIDEOPOSITIONWIDGET_H
#define VIDEOPOSITIONWIDGET_H

#include "basewidget.h"
#include "videoslider.h"

#include <QLabel>

class videoPositionWidget:public baseWidget
{
public:
    videoPositionWidget(QWidget *parent);

private:
    void initWidget();

public:
    videoSlider *m_slider;
    QLabel *m_currentTime;
    QLabel *m_totalTime;
protected:
    void mousePressEvent(QMouseEvent*);
};

#endif // VIDEOPOSITIONWIDGET_H
