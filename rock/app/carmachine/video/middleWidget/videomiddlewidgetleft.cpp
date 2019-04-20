#include "videomiddlewidgetleft.h"
#include <QHBoxLayout>
#include <QTime>
#include <QQuickItem>
#include "global_value.h"

videoMiddleWidgetLeft::videoMiddleWidgetLeft(QWidget *parent):baseWidget(parent)
{
    setObjectName("videoMiddleWidgetLeft");
    setStyleSheet("#videoMiddleWidgetLeft{background:rgb(10,10,10)}");
    initLayout();
    connect(m_positionWid->m_slider,SIGNAL(sig_sliderPositionChanged(int)),this,SIGNAL(sig_sliderPositionChanged(int)));
}

void videoMiddleWidgetLeft::initLayout()
{
    vmainlyout = new QVBoxLayout;

    m_contentWid = new videoQuickContentWidget(this);

#ifndef DEVICE_EVB
    // set tanslate update for px3se
    m_contentWid->setClearColor(QColor(Qt::transparent));
#endif

    m_contentWid->setResizeMode(QQuickWidget::SizeRootObjectToView);
#ifdef DEVICE_EVB
    m_contentWid->setSource(QUrl("qrc:/video3399.qml"));
#else
    m_contentWid->setSource(QUrl("qrc:/video.qml"));
#endif
    QObject* qmlMediaPlayer = m_contentWid->rootObject()->findChild<QObject*>("mediaPlayer");
    m_player = qvariant_cast<QMediaPlayer *>(qmlMediaPlayer->property("mediaObject"));

    //    m_contentWid = new videoContentWidget(this);

    m_positionWid = new videoPositionWidget(this);

    vmainlyout->addWidget(m_contentWid);
    vmainlyout->addWidget(m_positionWid);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(0);

    removePositionWidget();
    setLayout(vmainlyout);
}

void videoMiddleWidgetLeft::addPositionWidget()
{
    m_positionWid->show();
    vmainlyout->addWidget(m_positionWid);
    update();
}

void videoMiddleWidgetLeft::removePositionWidget()
{
    m_positionWid->hide();
    vmainlyout->removeWidget(m_positionWid);
    update();
}

void videoMiddleWidgetLeft::onDurationChanged(qint64 duration)
{
    m_positionWid->m_slider->setRange(0, duration);
    QTime totalTime((duration % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60),
                    (duration % (1000 * 60 * 60)) / (1000 * 60),
                    (duration % (1000 * 60)) / 1000);
    m_positionWid->m_totalTime->setText(totalTime.toString("hh:mm:ss"));
}

void videoMiddleWidgetLeft::onMediaPositionChanged(qint64 position)
{
    m_positionWid->m_slider->setValue(position);
    QTime currentTime((position % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60),
                      (position % (1000 * 60 * 60)) / (1000 * 60),
                      (position % (1000 * 60)) / 1000);
    m_positionWid->m_currentTime->setText(currentTime.toString("hh:mm:ss"));

}
