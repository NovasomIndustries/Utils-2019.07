#ifndef NETCONFIGDIALOG_H
#define NETCONFIGDIALOG_H

#include <QObject>
#include <QDialog>
#include "ui_networkconfig.h"
#include "rightstackedwidgets0.h"

class netConfigDialog:public QDialog,public Ui::NetworkConfig
{
    Q_OBJECT
public:
    netConfigDialog(QWidget *parent=0);

    virtual void paramsFromScanResults(netWork network);
    virtual int setNetworkParam(int id, const char *field,
                                const char *value, bool quote);
    virtual void paramsFromConfig(int network_id);
private:
    bool new_network;
    QString bssid;
    int edit_network_id;

    virtual void wepEnabled(bool enabled);
    virtual void getEapCapa();
protected:
    void resizeEvent(QResizeEvent *);
public slots:
    virtual void authChanged(int sel);
    virtual void eapChanged(int sel);
    virtual void addNetwork();
    virtual void encrChanged(const QString &sel);
    virtual void removeNetwork();
    virtual void writeWepKey(int network_id, QLineEdit *edit, int id);

};

#endif // NETCONFIGDIALOG_H
