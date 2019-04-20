#include "videopositionwidget.h"
#include <QHBoxLayout>
#include "global_value.h"

#ifdef DEVICE_EVB
int video_position_height = 60;
#else
int video_position_height = 35;
#endif

videoPositionWidget::videoPositionWidget(QWidget *parent):baseWidget(parent)
{
    setFixedHeight(video_position_height);
    setStyleSheet("background:rgb(31,31,31)");
    initWidget();
}

void videoPositionWidget::initWidget()
{
    QHBoxLayout *lyout = new QHBoxLayout;

    m_slider = new videoSlider(Qt::Horizontal,this);
    m_slider->setRange(0,0);

    m_currentTime = new QLabel("00:00",this);
    m_currentTime->setStyleSheet("color:rgb(150,150,150);");
    m_currentTime->setFixedHeight(video_position_height);
    m_currentTime->setAlignment(Qt::AlignVCenter);


    m_totalTime = new QLabel("00:00",this);
    m_totalTime->setStyleSheet("color:rgb(150,150,150);");
    m_totalTime->setFixedHeight(video_position_height);
    m_totalTime->setAlignment(Qt::AlignVCenter);


    lyout->addSpacing(10);
    lyout->addWidget(m_currentTime);
    lyout->addWidget(m_slider);
    lyout->addWidget(m_totalTime);
    lyout->addSpacing(10);
    lyout->setSpacing(10);
    lyout->setContentsMargins(0,0,0,0);

    QVBoxLayout *mainlyout = new QVBoxLayout;

    mainlyout->addLayout(lyout);
    mainlyout->setContentsMargins(0,0,0,0);

    setLayout(mainlyout);
}

void videoPositionWidget::mousePressEvent(QMouseEvent *event)
{
    if(m_slider->x() < event->x() && event->x() < (m_slider->x()+m_slider->width())){
        int dur = m_slider->maximum() - m_slider->minimum();
        int pos = m_slider->minimum() + dur * (((double)event->x()-m_slider->x())/ m_slider->width());
        if(pos != m_slider->sliderPosition()){
            m_slider->setValue(pos);
            emit m_slider->sig_sliderPositionChanged(pos);
        }
    }
}
