#ifndef BLUETOOTHSCANNERWIDGET_H
#define BLUETOOTHSCANNERWIDGET_H

#include "basewidget.h"
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothAddress>
#include <QMenu>

#include "ui_btscanner.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

QT_USE_NAMESPACE

class BluetoothScannerWidget:public baseWidget,public Ui::DeviceDiscovery
{
    Q_OBJECT
public:
    BluetoothScannerWidget(QWidget *parent = 0);
    ~BluetoothScannerWidget();

    void init();
public slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void on_power_clicked(bool clicked);
    void on_discoverable_clicked(bool clicked);
    void displayPairingMenu(const QPoint &pos);
    void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);
private slots:
    void startScan();
    void scanFinished();
    void setGeneralUnlimited(bool unlimited);
    void itemActivated(QListWidgetItem *item);
    void hostModeStateChanged(QBluetoothLocalDevice::HostMode);

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    Ui_DeviceDiscovery *ui;
};

#endif // BLUETOOTHSCANNERWIDGET_H
