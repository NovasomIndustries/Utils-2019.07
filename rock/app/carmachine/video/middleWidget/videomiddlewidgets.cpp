#include "videomiddlewidgets.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

videoMiddleWidgets::videoMiddleWidgets(QWidget *parent):baseWidget(parent)
{
#ifndef DEVICE_EVB
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    initLayout();
}

void videoMiddleWidgets::initLayout()
{
    QHBoxLayout *hmainlyout = new QHBoxLayout;

    m_stackWid = new QStackedWidget();

    m_rightWid = new videoMiddleWidgetRight(this);
    m_leftWid = new videoMiddleWidgetLeft(this);

    m_stackWid->addWidget(m_leftWid);
    m_stackWid->addWidget(m_rightWid);
    m_stackWid->setCurrentWidget(m_rightWid);
    isOnPlayMode = false;

    hmainlyout->addWidget(m_stackWid);
    hmainlyout->setContentsMargins(0,0,0,0);
    hmainlyout->setSpacing(0);

    setLayout(hmainlyout);
}

void videoMiddleWidgets::on_playMode(){
    m_stackWid->setCurrentWidget(m_leftWid);
    isOnPlayMode = true;
}

void videoMiddleWidgets::on_ListMode(){
    m_stackWid->setCurrentWidget(m_rightWid);
    isOnPlayMode = false;
}

