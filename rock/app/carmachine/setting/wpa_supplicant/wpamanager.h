#ifndef WPAMANAGER_H
#define WPAMANAGER_H

#include <QSystemTrayIcon>
#include <QObject>
#include <QTimer>
#include <QSocketNotifier>
#include <wpa_supplicant/wpamsg.h>

class wpaManager : public QObject
{
    Q_OBJECT

public:
    static wpaManager* getInstance(QObject *parent);

    virtual int ctrlRequest(const char *cmd, char *buf, size_t *buflen); // 向wpa_supplicant发送请求
    virtual void triggerUpdate();
    virtual void editNetwork(const QString &sel);
    virtual void removeNetwork(const QString &sel);
    virtual void enableNetwork(const QString &sel);
    virtual void disableNetwork(const QString &sel);
    virtual int getNetworkDisabled(const QString &sel);
    void setBssFromScan(const QString &bssid);
    void addInterface();
    int openCtrlConnection(const char *ifname);
#ifndef QT_NO_SESSIONMANAGER
    void saveState();

    void updateScanResult();        // 根据搜索到的结果更新界面
#endif

public slots:

    virtual void updateStatus();
    virtual void updateNetworks();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();
    virtual void scan();
    //    virtual void eventHistory();
    virtual void ping();
    virtual void signalMeterUpdate();
    virtual void processCtrlReq(const char *req);
    virtual void receiveMsgs();         // 发送请求后，接收消息从wpa_supplicant传递下来的消息
    virtual void processMsg(char *msg); // 与receiveMsgs配合使用，处理消息
    virtual void connectB();            // wpa_supplicant连接无线网络
    virtual void disconnectB();         // wpa_supplicant取消连接无线网络
    virtual void selectAdapter(const QString &sel); // 选择网卡设备
    virtual void selectNetwork(const QString &sel);
    virtual void editSelectedNetwork();
    virtual void editListedNetwork();
    virtual void removeSelectedNetwork();
    virtual void removeListedNetwork();
    virtual void addNetwork();
    virtual void enableAllNetworks();
    virtual void disableAllNetworks();
    virtual void removeAllNetworks();
    virtual void saveConfig();
    virtual void updateNetworkDisabledStatus();
    virtual void enableListedNetwork(bool);
    virtual void disableListedNetwork(bool);
    virtual void showTrayStatus();
    virtual void peersDialog();
    virtual void tabChanged(int index);
    virtual void wpsPbc();
    virtual void wpsGeneratePin();
    virtual void wpsApPinChanged(const QString &text);
    virtual void wpsApPin();
#ifdef CONFIG_NATIVE_WINDOWS
    virtual void startService();
    virtual void stopService();
#endif /* CONFIG_NATIVE_WINDOWS */

protected slots:


private:
    static wpaManager *_instance;
    wpaManager(QObject *parent=0);

    bool networkMayHaveChanged;
    char *ctrl_iface;
    struct wpa_ctrl *ctrl_conn;
    QSocketNotifier *msgNotifier;
    QTimer *timer;
    int pingsToStatusUpdate;
    WpaMsgList msgs;
    char *ctrl_iface_dir;
    struct wpa_ctrl *monitor_conn;
    //    UserDataRequest *udr;

    QString wpaStateTranslate(char *state);
    bool ackTrayIcon;
    bool startInTray;
    bool quietMode;

    bool wpsRunning;

    QString bssFromScan;

    void stopWpsRun(bool success);

    QTimer *signalMeterTimer;
    int signalMeterInterval;

#ifdef CONFIG_NATIVE_WINDOWS

    bool serviceRunning();
#endif /* CONFIG_NATIVE_WINDOWS */

    bool connectedToService;   // 标识是否已经连接上了wpa_supplicant服务
};

#endif /* WPAMANAGER_H */
