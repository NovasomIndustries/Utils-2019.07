#ifndef VOLWIDGET_H
#define VOLWIDGET_H

#include <QSlider>
#include "myslider.h"


class volWidget :public QWidget
{
    Q_OBJECT
public:
    volWidget(QWidget*parent);
    mySlider *m_slider_vol;
signals:
    void sig_valueChanged(int);
};

#endif // VOLWIDGET_H
