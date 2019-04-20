#include "bluetoothscannerwidget.h"
#include <QDebug>
#include "cmessagebox.h"
#include "global_value.h"

#ifdef DEVICE_EVB
int bt_button_width = 145;
int bt_button_height = 45;
int bt_item_height = 45;
#else
int bt_button_width = 80;
int bt_button_height = 30;
int bt_item_height = 25;
#endif


BluetoothScannerWidget::BluetoothScannerWidget(QWidget *parent)
    :baseWidget(parent),ui(new Ui_DeviceDiscovery)
{
    ui->setupUi(this);
    this->setObjectName("BluetoothScannerWidget");
    this->setStyleSheet("#BluetoothScannerWidget{background:rgb(33,36,43)}"
                        "QLabel{color:white}"
                        "QGroupBox{color:white}"
                        "QCheckBox{color:white}");
    ui->scan->setFixedSize(bt_button_width,bt_button_height);
    ui->clear->setFixedSize(bt_button_width,bt_button_height);
    ui->list->setStyleSheet("QListWidget{background:rgb(27,29,36)}");
}

void BluetoothScannerWidget::init(){
    localDevice = new QBluetoothLocalDevice;
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(ui->inquiryType, SIGNAL(toggled(bool)), this, SLOT(setGeneralUnlimited(bool)));
    connect(ui->scan, SIGNAL(clicked()), this, SLOT(startScan()));

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(addDevice(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

    connect(ui->list, SIGNAL(itemActivated(QListWidgetItem*)),
            this, SLOT(itemActivated(QListWidgetItem*)));
    connect(ui->list, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(itemActivated(QListWidgetItem*)));

    connect(localDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
            this, SLOT(hostModeStateChanged(QBluetoothLocalDevice::HostMode)));
    hostModeStateChanged(localDevice->hostMode());

    // add context menu for devices to be able to pair device
    ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayPairingMenu(QPoint)));
    connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing))
            , this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));
}

BluetoothScannerWidget::~BluetoothScannerWidget()
{
    delete discoveryAgent;
}

void BluetoothScannerWidget::addDevice(const QBluetoothDeviceInfo &info)
{
    QString label = QString("     %1            %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        item->setSizeHint(QSize(ui->list->width(),bt_item_height));
        item->setWhatsThis(info.address().toString());
        item->setToolTip(info.name());
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::blue));
        else
            item->setTextColor(QColor(Qt::white));

        ui->list->addItem(item);
    }

}

void BluetoothScannerWidget::startScan()
{
    discoveryAgent->start();
    ui->scan->setEnabled(false);
    ui->inquiryType->setEnabled(false);
}

void BluetoothScannerWidget::scanFinished()
{
    ui->scan->setEnabled(true);
    ui->inquiryType->setEnabled(true);
}

void BluetoothScannerWidget::setGeneralUnlimited(bool unlimited)
{
    if (unlimited)
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    else
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
}

void BluetoothScannerWidget::itemActivated(QListWidgetItem *item)
{
    QString btAddress = item->whatsThis();
    QString btName = item->toolTip();

    qDebug()<<"addressss:"<<btAddress;
    QBluetoothAddress address(btAddress);
    QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(address);
    if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
    {
        int result = CMessageBox::showCMessageBox(mainwid,"UnPair with "+btName.append("?"),"UnPair","Cancel");
        if(result == RESULT_CONFIRM)
        {
            localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
        }
    }
    else
    {
        int result = CMessageBox::showCMessageBox(mainwid,"Pair with "+btName.append("?"),"Pair","Cancel");
        if(result == RESULT_CONFIRM)
        {
            localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
        }
    }
}

void BluetoothScannerWidget::on_discoverable_clicked(bool clicked)
{
    if (clicked)
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
}

void BluetoothScannerWidget::on_power_clicked(bool clicked)
{
    if (clicked)
        localDevice->powerOn();
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
}

void BluetoothScannerWidget::hostModeStateChanged(QBluetoothLocalDevice::HostMode mode)
{
    if (mode != QBluetoothLocalDevice::HostPoweredOff)
        ui->power->setChecked(true);
    else
        ui->power->setChecked( false);

    if (mode == QBluetoothLocalDevice::HostDiscoverable)
        ui->discoverable->setChecked(true);
    else
        ui->discoverable->setChecked(false);

    bool on = !(mode == QBluetoothLocalDevice::HostPoweredOff);


    ui->scan->setEnabled(on);
    ui->discoverable->setEnabled(on);
}

void BluetoothScannerWidget::displayPairingMenu(const QPoint &pos)
{
    if (ui->list->count() == 0)
        return;
    QMenu menu(this);
    QAction *pairAction = menu.addAction("Pair");
    QAction *removePairAction = menu.addAction("Remove Pairing");
    QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
    QListWidgetItem *currentItem = ui->list->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if (index == -1)
        return;

    QBluetoothAddress address (text.left(index));
    if (chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if (chosenAction == removePairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
}

void BluetoothScannerWidget::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::blue));
        }
    } else {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::red));
        }
    }
}
