#ifndef CWAITDIALOG_H
#define CWAITDIALOG_H

#include <QDialog>
#include <qprogressindicator.h>

class CWaitDialog:public QDialog
{
public:
    CWaitDialog(QString waitText,QWidget *parent = 0);
private:
    QString m_waitText;
    QProgressIndicator *m_indecator;
private:
    void initWidget();
};

#endif // CWAITDIALOG_H
