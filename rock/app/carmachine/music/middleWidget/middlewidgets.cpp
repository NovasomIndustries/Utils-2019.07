#include "middlewidgets.h"

#include <QHBoxLayout>
#include <QPainter>

middleWidgets::middleWidgets(QWidget *parent) : baseWidget(parent)
{
    setObjectName("middleWidgets");
    setStyleSheet("#middleWidgets{background:white}"
                  "QLabel{color:black}");
    initLayout();
}

void middleWidgets::initLayout()
{
    QHBoxLayout *hyout=new QHBoxLayout;

    m_leftWid=new middleWidgetLeft(this);
    m_rightWid = new middleWidgetRight(this);

    hyout->addWidget(m_leftWid,1);
    hyout->addWidget(m_rightWid,3);
    hyout->setSpacing(0);
    hyout->setContentsMargins(0,0,0,0);
    setLayout(hyout);
}

void middleWidgets::setInitMainWidget(musicWidgets *musicWidgets)
{
    m_mainWid = musicWidgets;
    m_leftWid->setInitMainWidgets(m_mainWid);
}

