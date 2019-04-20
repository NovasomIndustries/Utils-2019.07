#include "settingmiddlewidgets.h"
#include <QHBoxLayout>

settingMiddleWidgets::settingMiddleWidgets(QWidget *parent):baseWidget(parent)
{
    initLayout();
    initConnection();
}

void settingMiddleWidgets::initLayout()
{
    QHBoxLayout *hmainlyout = new QHBoxLayout;

    m_leftWid = new leftWidgets(this);
    m_stackedWid = new QStackedWidget(this);

    m_wifiWid = new rightStackedWidgets0(m_stackedWid);
    m_otherWid = new rightStackedWidgets1(m_stackedWid);

    m_stackedWid->addWidget(m_wifiWid);
    m_stackedWid->addWidget(m_otherWid);

    hmainlyout->addWidget(m_leftWid,1);
    hmainlyout->addWidget(m_stackedWid,4);

    hmainlyout->setContentsMargins(0,0,0,0);
    hmainlyout->setSpacing(0);
    setLayout(hmainlyout);
}

void settingMiddleWidgets::initConnection()
{
    connect(m_leftWid->m_funtionlist,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_currentWidgetChanged(int)));
    slot_currentWidgetChanged(0);
}

void settingMiddleWidgets::slot_currentWidgetChanged(int index)
{
    m_leftWid->m_funtionlist->setCurrentCell(index,0);
    switch(index){
    case 0:
        m_stackedWid->setCurrentIndex(0);
        break;
    default:
        m_otherWid->initBluetooth();
        m_stackedWid->setCurrentIndex(1);
        break;
    }
}
