#ifndef RIGHTSTACKEDWIDGETS1_H
#define RIGHTSTACKEDWIDGETS1_H

#include <basewidget.h>
#include "bluetoothscannerwidget.h"



class rightStackedWidgets1:public baseWidget
{
    Q_OBJECT
public:
    rightStackedWidgets1(QWidget *parent);

    void initBluetooth();
private:
    BluetoothScannerWidget *m_scannerWidget;

    void initData();
    void initLayout();
};



#endif // RIGHTSTACKEDWIDGETS1_H
