#ifndef RIGHTSTACKEDWIDGETS0_H
#define RIGHTSTACKEDWIDGETS0_H

#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QTabWidget>
#include <QTimer>
#include <QThread>
#include <QLineEdit>
#include "basewidget.h"
#include "basepushbutton.h"
#include "wlanlisttable.h"
#include "wpa_supplicant/wpamanager.h"
#include "cswitchbutton.h"

class switchWidget;
class tabCurrentStatus;
class tabScanResult;
//class tabApHotspot;
class myNetThread;

struct netWork   // Wifi信息结构体
{
    QString SSID;
    QString BSSID;
    QString frequence;
    QString signal;
    QString flags;
};

class rightStackedWidgets0:public baseWidget
{
    Q_OBJECT
public:
    rightStackedWidgets0(QWidget *parent);

    switchWidget *m_wifiSwitch;   // 开关控件
    QTabWidget *m_tab;           // TabWidget 包含status、Scan result二个部分
    tabCurrentStatus *m_tabCurrentStatus;
    tabScanResult *m_tabScanResult;
//    tabApHotspot *m_tabHotspot;
	// about ap
	switchWidget *mApSwitch;
    QLineEdit *mHostApName;
    QLineEdit *mHostApPassWord;

    wpaManager *m_netManager; // 网络管理类
public:
    void getIPAdress();
private:
    void initData();
    void initLayout();
    void initConnection();
    void wifiStationOn();
    void wifiStationOff();
    void wifiAccessPointOn();
    void wifiAccessPointOff();

    QTimer *m_workTimer;
public slots:
    void slot_showItemDetail(int,int);
    void slot_onToggled(bool isChecked);
    void slot_checkLanConnection();
	// about ap
	void onAPToggled(bool isChecked);
    void setAPUnchecked();
	void setWifiUnchecked();
signals:

};


// 控制开关Widget:包含一个开关控件和一个开关状态提示字体
class switchWidget:public baseWidget
{
public:
    switchWidget(QWidget *parent,QString text);
    CSwitchButton* getSwitchButton(){return m_btnSwitch;}
private:
    QLabel *m_lblState;
    CSwitchButton *m_btnSwitch;

};

// TabWidget中当前状态布局
class tabCurrentStatus:public baseWidget
{
public:
    tabCurrentStatus(QWidget *parent);

    QLabel *textStatus;
    QLabel *textLastMsg;
    QLabel *textAuthentication;
    QLabel *textEncryption;
    QLabel *textSSID;
    QLabel *textBSSID;
    QLabel *textIPAddress;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
private:
};

class tabScanResult:public baseWidget
{
public:
    tabScanResult(QWidget *parent);

    wlanListTable *m_table;
    QPushButton *scanButton;

    struct netWork* m_netWorks = new struct netWork[200];

    void clearTable();
    void insertIntoTable(QString name,QString lock,QString siganl,QString detail);
protected:

};

//// tabWidget中 <无线热点> 布局
//class tabApHotspot:public baseWidget
//{
//public:
//    tabApHotspot(QWidget *parent);

//    switchButton *m_hotspotSwitch;
//    QLineEdit *m_hotspotNameEdit;
//    QPushButton *m_confirmButton;
//};

class myNetThread:public QThread
{
public:
    myNetThread(QObject *parent = 0): QThread(parent){}
protected:
    virtual void run();
private:
};

#endif // RIGHTSTACKEDWIDGETS0_H
