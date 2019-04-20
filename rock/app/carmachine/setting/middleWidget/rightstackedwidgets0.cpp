#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
//#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <poll.h>
#include <stdbool.h>
#include "rightstackedwidgets0.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QThread>
#include "netconfigdialog.h"
#include "global_value.h"
#include <cmessagebox.h>

#ifdef DEVICE_EVB
int wifi_button_width = 145;
int wifi_button_height = 45;
int wifi_switch_width = 80;
int wifi_switch_height = 40;
#else
int wifi_button_width = 80;
int wifi_button_height = 30;
int wifi_switch_width = 40;
int wifi_switch_height = 20;
#endif

#define DBG false

#if DBG
#define DEBUG_INFO(M, ...) qDebug("DEBUG %d: " M, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_INFO(M, ...) do {} while (0)
#endif

#define DEBUG_ERR(M, ...) qDebug("DEBUG %d: " M, __LINE__, ##__VA_ARGS__)

bool	lanOldState = false;
bool	lanNewState = false;

static const char WPA_SUPPLICANT_CONF_DIR[]           = "/tmp/wpa_supplicant.conf";
static const char HOSTAPD_CONF_DIR[]	=	"/tmp/hostapd.conf";
int is_supplicant_running();

const bool console_run(const char *cmdline) {
    DEBUG_INFO("cmdline = %s\n",cmdline);

#if 0
    FILE *fp = popen(cmdline, "r");
    if (!fp) {
        DEBUG_ERR("Running cmdline failed: %s\n", cmdline);
        return false;
    }

    pclose(fp);
#else
    int ret;
    ret = system(cmdline);
    if(ret < 0){
        DEBUG_ERR("Running cmdline failed: %s\n", cmdline);
    }
#endif

    return true;
}

int get_pid(char *Name) {
    int len;
    char name[20] = {0};
    len = strlen(Name);
    strncpy(name,Name,len);
    name[len] ='\0';
    char cmdresult[256] = {0};
    char cmd[20] = {0};
    FILE *pFile = NULL;
    int  pid = 0;

    sprintf(cmd, "pidof %s", name);
    pFile = popen(cmd, "r");
    if (pFile != NULL)  {
        while (fgets(cmdresult, sizeof(cmdresult), pFile)) {
            pid = atoi(cmdresult);
            DEBUG_INFO("--- %s pid = %d ---\n",name,pid);
            break;
        }
    }
    pclose(pFile);
    return pid;
}

// about wifi
int creat_supplicant_file()
{
    FILE* fp;
    fp = fopen(WPA_SUPPLICANT_CONF_DIR, "wt+");

    if (fp != 0) {
        fputs("ctrl_interface=/var/run/wpa_supplicant\n", fp);
        fputs("ap_scan=1\n", fp);
        fclose(fp);
        return 0;
    }
    return -1;
}

int creat_hostapd_file(const char* name, const char* password) {
    FILE* fp;
    fp = fopen(HOSTAPD_CONF_DIR, "wt+");

    if (fp != 0) {
        fputs("interface=wlan0\n", fp);
        fputs("driver=nl80211\n", fp);
        fputs("ssid=", fp);
        fputs(name, fp);
        fputs("\n", fp);
        fputs("channel=6\n", fp);
        fputs("hw_mode=g\n", fp);
        fputs("ieee80211n=1\n", fp);
        fputs("ht_capab=[SHORT-GI-20]\n", fp);
        fputs("ignore_broadcast_ssid=0\n", fp);
        fputs("auth_algs=1\n", fp);
        fputs("wpa=3\n", fp);
        fputs("wpa_passphrase=", fp);
        fputs(password, fp);
        fputs("\n", fp);
        fputs("wpa_key_mgmt=WPA-PSK\n", fp);
        fputs("wpa_pairwise=TKIP\n", fp);
        fputs("rsn_pairwise=CCMP", fp);

        fclose(fp);
        return 0;
    }
    return -1;
}

int is_hostapd_running()
{
    int ret;

    ret = get_pid("hostapd");

    return ret;
}

int wifi_start_hostapd()
{
    if (is_hostapd_running()) {
        return 0;
    }
    console_run("ifconfig wlan0 up");
    console_run("ifconfig wlan0 192.168.100.1 netmask 255.255.255.0");
    console_run("echo 1 > /proc/sys/net/ipv4/ip_forward");
    console_run("iptables --flush");
    console_run("iptables --table nat --flush");
    console_run("iptables --delete-chain");
    console_run("iptables --table nat --delete-chain");
    console_run("iptables --table nat --append POSTROUTING --out-interface eth0 -j MASQUERADE");
    console_run("iptables --append FORWARD --in-interface wlan0 -j ACCEPT");
    console_run("/usr/sbin/hostapd /tmp/hostapd.conf -B");

    return 0;
}

int is_supplicant_running()
{
    int ret;

    ret = get_pid("wpa_supplicant");

    return ret;
}

int wifi_start_supplicant()
{
    if (is_supplicant_running()) {
        return 0;
    }

    console_run("/usr/sbin/wpa_supplicant -Dnl80211 -iwlan0 -c /tmp/wpa_supplicant.conf &");

    return 0;
}

int wifi_stop_supplicant()
{
    int pid;
    char *cmd = NULL;

    /* Check whether supplicant already stopped */
    if (!is_supplicant_running()) {
          return 0;
    }

    pid = get_pid("wpa_supplicant");
    asprintf(&cmd, "kill %d", pid);
    console_run(cmd);
    free(cmd);

    return 0;
}


int wifi_stop_hostapd()
{
    int pid;
    char *cmd = NULL;

    if (!is_hostapd_running()) {
        return 0;
    }
    pid = get_pid("hostapd");
    asprintf(&cmd, "kill %d", pid);
    console_run(cmd);
    free(cmd);

    console_run("echo 0 > /proc/sys/net/ipv4/ip_forward");
    console_run("ifconfig wlan0 down");
    return 0;
}


rightStackedWidgets0::rightStackedWidgets0(QWidget *parent):baseWidget(parent)
{
    setObjectName("rightStackedWidgets0");
    setStyleSheet("#rightStackedWidgets0{background:rgb(33,36,43)}");
    initLayout();
    initData();
    initConnection();  // 连接信号与槽
}

void rightStackedWidgets0::initData()
{
    wifiWid = this;
    m_netManager = wpaManager::getInstance(this);
    m_wifiSwitch->getSwitchButton()->setChecked(is_supplicant_running());
	mApSwitch->getSwitchButton()->setChecked(is_hostapd_running());
    if(is_supplicant_running())
    {
        m_netManager->openCtrlConnection("wlan0");
    }
}

void rightStackedWidgets0::initLayout()
{
    // 第1行布局 开关
    m_wifiSwitch = new switchWidget(this,"Open Wifi");


    // 第2部分布局 TabWidget 包含2部分内容:Current status、WifiList
    m_tab = new QTabWidget(this);
    m_tab->setStyleSheet("background:rgb(33,36,43)");

    m_tabCurrentStatus = new tabCurrentStatus(this);
    m_tabScanResult = new tabScanResult(this);
    //    m_tabHotspot = new tabApHotspot(this);
    m_tab->addTab(m_tabScanResult,QString("Scan Result"));
    m_tab->addTab(m_tabCurrentStatus,QString("Current Status"));
    //    m_tab->addTab(m_tabHotspot,QString("HotSpot"));
    m_tab->setCurrentIndex(0);
	
	// 第3部分布局 AP
	mApSwitch = new switchWidget(this,"Start HostAp");

    QFrame *bottomLine = new QFrame(this);
    bottomLine->setFixedHeight(2);
    bottomLine->setStyleSheet("QFrame{border:1px solid rgb(100,100,100,255);}");
    bottomLine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    // Host AP name layout
    QLabel *apNameLabel = new QLabel(this);
    apNameLabel->setText("HostAp Name:");

    mHostApName = new QLineEdit("RK_HOSTAP_TEST",this);
    mHostApName->setFixedSize(wifi_button_width + 200,wifi_button_height);
    mHostApName->setAlignment(Qt::AlignRight);

    QHBoxLayout *apNameLayout = new QHBoxLayout;
    apNameLayout->addWidget(apNameLabel);
    apNameLayout->addWidget(mHostApName);

    // Host AP password layout
    QLabel *apPasswordLabel = new QLabel(this);
    apPasswordLabel->setText("HostAp password:");

    mHostApPassWord = new QLineEdit("987654321",this);
    mHostApPassWord->setFixedSize(wifi_button_width + 200,wifi_button_height);
    mHostApPassWord->setAlignment(Qt::AlignRight);

    QHBoxLayout *apPasswordLayout = new QHBoxLayout;
    apPasswordLayout->addWidget(apPasswordLabel);
    apPasswordLayout->addWidget(mHostApPassWord);


    QVBoxLayout *vmainlyout = new QVBoxLayout;
    vmainlyout->addSpacing(20);
    vmainlyout->addWidget(m_wifiSwitch);
    vmainlyout->addWidget(m_tab);
	// ap
	vmainlyout->addWidget(bottomLine);
    vmainlyout->addLayout(apNameLayout);
    vmainlyout->addLayout(apPasswordLayout);
	vmainlyout->addWidget(mApSwitch);
	
	vmainlyout->addSpacing(50);
    vmainlyout->addStretch(0);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(12);

    // 空间太大显示不便，加一个横向的布局
    QHBoxLayout *hmainlyout = new QHBoxLayout;
    hmainlyout->addStretch(1);
    hmainlyout->addLayout(vmainlyout,4);
    hmainlyout->addStretch(1);
    setLayout(hmainlyout);
}

void rightStackedWidgets0::initConnection()
{
    if (access(WPA_SUPPLICANT_CONF_DIR, F_OK) < 0) {
        creat_supplicant_file();
    }
    creat_hostapd_file("RK_HOSTAPD_TEST", "12345678");

    //    connect(m_adapterSeletor,SIGNAL(activated(const QString&)),m_netManager,SLOT(selectAdapter(const QString&)));

    connect(m_tabCurrentStatus->connectButton,SIGNAL(clicked(bool)),m_netManager,SLOT(connectB()));
    connect(m_tabCurrentStatus->disconnectButton,SIGNAL(clicked(bool)),m_netManager,SLOT(disconnectB()));
    connect(m_tabScanResult->scanButton,SIGNAL(clicked(bool)),m_netManager,SLOT(scan()));

    connect(m_tabScanResult->m_table,SIGNAL(cellClicked(int,int)),this,SLOT(slot_showItemDetail(int,int)));
    connect(m_wifiSwitch->getSwitchButton(),SIGNAL(checkStateChanged(bool)),this,SLOT(slot_onToggled(bool)));
	
	connect(mApSwitch->getSwitchButton(),SIGNAL(checkStateChanged(bool)),this,SLOT(onAPToggled(bool)));

    m_workTimer = new QTimer(this);
    m_workTimer->setSingleShot(false);
#ifdef DEVICE_EVB
    connect(m_workTimer, SIGNAL(timeout()), this, SLOT(slot_checkLanConnection()));
    m_workTimer->start(5000);
#endif
}

void rightStackedWidgets0::slot_showItemDetail(int row,int)
{
    netConfigDialog *dialog = new netConfigDialog(this);
    if (dialog == NULL)
        return;
    dialog->paramsFromScanResults(m_tabScanResult->m_netWorks[row]);
    dialog->show();
}


void rightStackedWidgets0::wifiStationOn()
{

    myNetThread *thread = new myNetThread;
    thread->start();
    m_netManager->openCtrlConnection("wlan0");
}

void rightStackedWidgets0::wifiStationOff()
{
    wifi_stop_supplicant();
    m_tabScanResult->clearTable();
}

void myNetThread::run()
{
    wifi_start_supplicant();
}

void rightStackedWidgets0::wifiAccessPointOn()
{
    wifi_start_hostapd();
}

void rightStackedWidgets0::wifiAccessPointOff()
{
    wifi_stop_hostapd();
}

void rightStackedWidgets0::slot_onToggled(bool isChecked)
{
    if(isChecked){
		if(is_hostapd_running()){
			CMessageBox::showCMessageBox(this,"Close hostap first","Confirm","Cancel");
			QTimer::singleShot(10,this,SLOT(setWifiUnchecked()));
		}else{
			DEBUG_INFO("=======wifiStationOn========\n");
			wifiStationOn();
		}
    }else{
        DEBUG_INFO("=======wifiStationOff========\n");
        wifiStationOff();
    }
}

void rightStackedWidgets0::onAPToggled(bool isChecked){
    if(isChecked){
        if(mHostApName->text()== NULL || mHostApPassWord->text().size() < 8){
            QMessageBox::warning(this,"Warning","name can't be null,and password can't be less 8!",QMessageBox::Ok);
			QTimer::singleShot(10,this,SLOT(setAPUnchecked()));
        }else if(is_supplicant_running()){
			CMessageBox::showCMessageBox(this,"Close wifi first.","Confirm","Cancel");
			QTimer::singleShot(10,this,SLOT(setAPUnchecked()));
		}else {
			creat_hostapd_file(mHostApName->text().toLatin1().data(),mHostApPassWord->text().toLatin1().data());
			wifi_start_hostapd();
		}
    }else{
        wifi_stop_hostapd();
    }
}

void rightStackedWidgets0::setAPUnchecked()
{
    mApSwitch->getSwitchButton()->setChecked(false);
}

void rightStackedWidgets0::setWifiUnchecked()
{
    m_wifiSwitch->getSwitchButton()->setChecked(false);
}


void lanStateChanhe(bool state){
    //need to check wifi state
    if(state){
        console_run("ifconfig eth0 up");
        console_run("udhcpc -i eth0");
    }else{
        console_run("ifconfig eth0 down");
    }
}

void rightStackedWidgets0::getIPAdress()
{
    console_run("udhcpc -i wlan0 &");
}

void rightStackedWidgets0::slot_checkLanConnection()
{
    char cmdbuf[1024] = {0};
    char cmdresult[1024] = {0};

    sprintf(cmdbuf, "cat /sys/class/net/eth0/carrier");
    FILE *pp = popen(cmdbuf, "r");
    if (!pp) {
        DEBUG_ERR("Running cmdline failed:cat /sys/class/net/eth0/carrier\n");
        return;
    }
    fgets(cmdresult, sizeof(cmdresult), pp);
    pclose(pp);

    if(strstr(cmdresult, "1"))
    {
        lanNewState = true;
    }else if(strstr(cmdresult, "0")){
        lanNewState = false;
    }else{
        console_run("ifconfig eth0 up");
    }
    if(lanOldState != lanNewState){
        if(lanNewState){
            //LanConnected
            lanStateChanhe(lanNewState);
        }else{
            //LanDisconnected
            lanStateChanhe(lanNewState);
        }
        lanOldState = 	lanNewState;
    }

}
switchWidget::switchWidget(QWidget *parent,QString text):baseWidget(parent)
{
	setFixedHeight(wifi_switch_height);
    QHBoxLayout *mainlyout = new QHBoxLayout;

    m_lblState = new QLabel(this);
    m_lblState->setText(text);

    m_btnSwitch = new CSwitchButton(this);
    m_btnSwitch->setFixedSize(wifi_switch_width,wifi_switch_height);

    mainlyout->addWidget(m_lblState);
    mainlyout->addWidget(m_btnSwitch);
    mainlyout->setContentsMargins(0,0,0,0);
    mainlyout->setSpacing(0);

    setLayout(mainlyout);
}


// tabWidget中current status布局的初始化
tabCurrentStatus::tabCurrentStatus(QWidget *parent):baseWidget(parent)
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    // lyout1_Status
    QHBoxLayout *lyout1 = new QHBoxLayout;
    QLabel *statusLabel = new QLabel(this);
    statusLabel->setText("Status:");

    textStatus = new QLabel(this);
    textStatus->setText(QString("connected"));
    lyout1->addWidget(statusLabel,1);
    lyout1->addWidget(textStatus,2);

    //lyout2_Last Message
    QHBoxLayout *lyout2 = new QHBoxLayout;
    QLabel *lastMessageLabel = new QLabel(this);
    lastMessageLabel->setText("Last message:");

    textLastMsg = new QLabel(this);
    textLastMsg->setText(QString());
    lyout2->addWidget(lastMessageLabel,1);
    lyout2->addWidget(textLastMsg,2);

    // lyou3_Authenticant
    QHBoxLayout *lyout3 = new QHBoxLayout;
    QLabel *authenticationLabel = new QLabel(this);
    authenticationLabel->setText("Authentication:");

    textAuthentication = new QLabel(this);
    textAuthentication->setText(QString("None"));
    lyout3->addWidget(authenticationLabel,1);
    lyout3->addWidget(textAuthentication,2);

    //lyout4_Encryption
    QHBoxLayout *lyout4 = new QHBoxLayout;
    QLabel *encryptionLabel = new QLabel(this);
    encryptionLabel->setText("EncryptionLabel:");

    textEncryption = new QLabel(this);
    textEncryption->setText(QString("None"));
    lyout4->addWidget(encryptionLabel,1);
    lyout4->addWidget(textEncryption,2);

    //lyout5_SSID
    QHBoxLayout *lyout5 = new QHBoxLayout;
    QLabel *ssidLabel = new QLabel(this);
    ssidLabel->setText("SSID:");

    textSSID = new QLabel(this);
    textSSID->setText(QString("None"));
    lyout5->addWidget(ssidLabel,1);
    lyout5->addWidget(textSSID,2);


    //lyout6_BSSID
    QHBoxLayout *lyout6 = new QHBoxLayout;
    QLabel *bssidLabel = new QLabel(this);
    bssidLabel->setText("BSSID:");

    textBSSID = new QLabel(this);
    textBSSID->setText(QString("None"));
    lyout6->addWidget(bssidLabel,1);
    lyout6->addWidget(textBSSID,2);

    //lyout7_IP address
    QHBoxLayout *lyout7 = new QHBoxLayout;
    QLabel *ipAddressLabel = new QLabel(this);
    ipAddressLabel->setText("IP Address:");

    textIPAddress = new QLabel(this);
    textIPAddress->setText(QString("None"));
    lyout7->addWidget(ipAddressLabel,1);
    lyout7->addWidget(textIPAddress,2);

    //lyout8 connect and disconnect button
    QHBoxLayout *lyout8 = new QHBoxLayout;
    connectButton = new QPushButton("Connect",this);
    connectButton->setStyleSheet("QPushButton{color:white}");
    connectButton->setFixedSize(wifi_button_width,wifi_button_height);

    disconnectButton = new QPushButton("Disconnect",this);
    disconnectButton->setStyleSheet("QPushButton{color:white}");
    disconnectButton->setFixedSize(wifi_button_width,wifi_button_height);
    lyout8->addStretch(0);
    lyout8->addWidget(connectButton);
    lyout8->addSpacing(30);
    lyout8->addWidget(disconnectButton);
    lyout8->addStretch(0);

    vmainlyout->addLayout(lyout1);
    vmainlyout->addLayout(lyout2);
    vmainlyout->addLayout(lyout3);
    vmainlyout->addLayout(lyout4);
    vmainlyout->addLayout(lyout5);
    vmainlyout->addLayout(lyout6);
    vmainlyout->addLayout(lyout7);
    vmainlyout->addSpacing(40);
    vmainlyout->addLayout(lyout8);
    vmainlyout->addStretch(0);
    vmainlyout->setContentsMargins(30,30,10,10);

    setLayout(vmainlyout);
}

// tabWigdet中Scan Result布局的初始化
tabScanResult::tabScanResult(QWidget *parent):baseWidget(parent)
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    // lyout1
    QLabel *tipLabel = new QLabel("the scan result:",this);

    // lyout2
    m_table = new wlanListTable(this);

    // lyout3
    QHBoxLayout *lyout1 = new QHBoxLayout;
    scanButton = new QPushButton("reScan",this);
    scanButton->setStyleSheet("QPushButton{color:white}");
    scanButton->setFixedSize(wifi_button_width,wifi_button_height);

    lyout1->addStretch(0);
    lyout1->addWidget(scanButton);
    lyout1->addStretch(0);

    vmainlyout->addWidget(tipLabel);
    vmainlyout->addSpacing(5);
    vmainlyout->addWidget(m_table);
    vmainlyout->addSpacing(15);
    vmainlyout->addLayout(lyout1);
    vmainlyout->setContentsMargins(40,40,20,20);
    vmainlyout->setSpacing(5);
    setLayout(vmainlyout);
}

void tabScanResult::clearTable()
{
    int iLen = m_table->rowCount();
    for(int i=0;i<iLen;i++)
    {
        m_table->removeRow(0);
    }
    m_table->clear();
}

void tabScanResult::insertIntoTable(QString ssid, QString bssid, QString siganl, QString flags)
{
    int rowCount = m_table->rowCount();
    m_table->insertRow(rowCount);

    m_table->setItem(rowCount,0,new QTableWidgetItem(ssid));
    m_table->setItem(rowCount,1,new QTableWidgetItem(bssid));
    m_table->item(rowCount,0)->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_table->item(rowCount,1)->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    // 设置Wifi等级图标
    int siganlValue = siganl.toInt();
    QTableWidgetItem *siganlItem;
    if(siganlValue>=(-55)){
        siganlItem = new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_signal_4_dark.png"),NULL);
    }else if(siganlValue>=(-70)){
        siganlItem = new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_signal_3_dark.png"),NULL);
    }else if(siganlValue>=(-85)){
        siganlItem = new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_signal_2_dark.png"),NULL);
    }else{
        siganlItem = new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_signal_1_dark.png"),NULL);
    }
    m_table->setItem(rowCount,2,siganlItem);
    m_table->item(rowCount,2)->setData(Qt::DisplayRole,siganlValue);


    // 设置安全性图标
    QString auth;
    if (flags.indexOf("[WPA2-EAP") >= 0)
        auth = "WPA2_EAP";
    else if (flags.indexOf("[WPA-EAP") >= 0)
        auth = "WPA_EAP";
    else if (flags.indexOf("[WPA2-PSK") >= 0)
        auth = "WPA2_PSK";
    else if (flags.indexOf("[WPA-PSK") >= 0)
        auth = "WPA_PSK";
    else
        auth = "OPEN";

    if(auth.compare("OPEN")==0)
    {
        m_table->setItem(rowCount,3,new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_unlocked.png"),auth));
    }else{
        m_table->setItem(rowCount,3,new QTableWidgetItem(QIcon(":/image/setting/ic_wifi_locked.png"),auth));
    }

    // 将数据存入数据结构
    m_netWorks[rowCount].SSID = ssid;
    m_netWorks[rowCount].BSSID = bssid;
    m_netWorks[rowCount].signal = siganl;
    m_netWorks[rowCount].flags = flags;

//    m_table->sortByColumn(2);

//    // 数据存入结构体数组中
//    for(int i=0;i<m_table->rowCount();i++)
//    {
//        m_netWorks[i].SSID = m_table->itemAt(i,0)->text();
//        m_netWorks[i].BSSID = m_table->itemAt(i,1)->text();
//        m_netWorks[i].signal = m_table->itemAt(i,2)->data(Qt::DisplayRole).toString();
//        m_netWorks[i].flags = m_table->itemAt(i,3)->text();
//    }
}

//tabApHotspot::tabApHotspot(QWidget *parent):baseWidget(parent)
//{
//    QVBoxLayout *vmainlyout = new QVBoxLayout;

//    // layout1 hotspot button
//    QHBoxLayout *lyout1 = new QHBoxLayout;
//    QLabel *switchText = new QLabel("Hotspot Switch:",this);
//    switchText->setFont(QFont("Microsoft YaHei",12,QFont::Normal));

//    m_hotspotSwitch = new switchButton(this);
//    m_hotspotSwitch->setFixedSize(40,20);
//    lyout1->addWidget(switchText);
//    lyout1->addWidget(m_hotspotSwitch);

//    //layout2 hotspot name edit
//    QHBoxLayout *lyout2 = new QHBoxLayout;
//    QLabel *hotspotNameText = new QLabel("Hotspot Name:",this);
//    hotspotNameText->setFont(QFont("Microsoft YaHei",12,QFont::Normal));

//    m_hotspotNameEdit = new QLineEdit(this);
//    m_hotspotNameEdit->setText("hotspot Name");

//    lyout2->addWidget(hotspotNameText);
//    lyout2->addWidget(m_hotspotNameEdit);

//    //layout3 confirm button
//    m_confirmButton = new QPushButton("confirm",this);
//    m_confirmButton->setStyleSheet("QPushButton{background:rgb(85,92,108)}"
//                              "QPushButton{color:white}"
//                              "QPushButton{border-radius:5px}");
//    m_confirmButton->setFixedSize(70,28);

//    vmainlyout->addSpacing(30);
//    vmainlyout->addLayout(lyout1);
//    vmainlyout->addLayout(lyout2);
//    vmainlyout->addSpacing(20);
//    vmainlyout->addWidget(m_confirmButton);
//    vmainlyout->addStretch(0);

//    vmainlyout->setContentsMargins(20,10,20,20);
//    vmainlyout->setSpacing(10);
//    setLayout(vmainlyout);
//}

