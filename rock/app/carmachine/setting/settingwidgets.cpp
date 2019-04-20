#include "settingwidgets.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

settingWidgets::settingWidgets(QWidget *parent):baseWidget(parent)
{
    setStyleSheet("QLabel{color:white;}");
    initLayout();
}


void settingWidgets::initLayout()
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    m_topWid = new settingTopWidgets(this);
    m_middleWid = new settingMiddleWidgets(this);

    vmainlyout->addWidget(m_topWid);
    vmainlyout->addWidget(m_middleWid);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(0);

    setLayout(vmainlyout);
}
