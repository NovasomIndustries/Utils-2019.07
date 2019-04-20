#include "musicpositionwidget.h"


#include "global_value.h"
#include "mainWindows/mainwindow.h"
#include <QVBoxLayout>

musicPositionWidget::musicPositionWidget(QWidget *parent):QWidget(parent)
{
    initWidget();
    setFixedHeight(80);
}

void musicPositionWidget::initWidget()
{
    QVBoxLayout *mainlyout = new QVBoxLayout;

    m_mainslider=new mySlider(Qt::Horizontal,this);
    m_mainslider->setRange(0,1000);
    m_mainslider->setMinimumSize(403,12);
    m_mainslider->setMaximumHeight(12);
    m_mainslider->setStyleSheet("QSlider::groove:horizontal{border-radius:4px;height:10px;}"
                                "QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
                                "QSlider::add-page:horizontal{background:rgb(200,200,209);}"
                                "QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");

    mainlyout->addWidget(m_mainslider);
    mainlyout->setSpacing(0);
    mainlyout->setContentsMargins(0,0,0,0);

    setLayout(mainlyout);
}

void musicPositionWidget::mousePressEvent(QMouseEvent *event)
{
    if(m_mainslider->x() < event->x() && event->x() < (m_mainslider->x()+m_mainslider->width())){
        int dur = m_mainslider->maximum() - m_mainslider->minimum();
        int pos = m_mainslider->minimum() + dur * (((double)event->x()-m_mainslider->x())/ m_mainslider->width());
        if(pos != m_mainslider->sliderPosition()){
            m_mainslider->setValue(pos);
            emit mainwid->getMusicWidget()->getPlayer()->setPosition(pos);
        }
    }
}
