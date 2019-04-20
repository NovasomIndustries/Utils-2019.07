#include "rightstackedwidgets1.h"

rightStackedWidgets1::rightStackedWidgets1(QWidget *parent):baseWidget(parent)
{
    setObjectName("rightStackedWidgets1");
    setStyleSheet("#rightStackedWidgets1{background:rgb(33,36,43)}");
    initData();
    initLayout();
}

void rightStackedWidgets1::initData()
{
    m_scannerWidget = new BluetoothScannerWidget(this);
}

void rightStackedWidgets1::initBluetooth(){
    m_scannerWidget->init();
}

void rightStackedWidgets1::initLayout()
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;
    vmainlyout->addSpacing(30);
    vmainlyout->addWidget(m_scannerWidget);
    vmainlyout->addSpacing(20);
    vmainlyout->addStretch(0);
    vmainlyout->setContentsMargins(0,0,0,0);

    QHBoxLayout *hmainlyout = new QHBoxLayout;
    hmainlyout->addStretch(1);
    hmainlyout->addLayout(vmainlyout,4);
    hmainlyout->addStretch(1);
    setLayout(hmainlyout);
}

