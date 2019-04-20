#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QObject>

#include "basewindow.h"
#include "mainwidgetup.h"
#include "mainwidgetlow.h"
#include "musicwidgets.h"
#include "camerawidgets.h"
#include "videowidgets.h"
#include "settingwidgets.h"
#include "gallerywidgets.h"

#include <QPropertyAnimation>
#include <QStackedLayout>
#include <QProcess>
#include "cwaitdialog.h"

class galleryWidgets;

class mainWindow : public baseWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);
private:
    void initLayout();
    void initConnection();
    void initAnimation();
    void closeCameraApp();
public:
    QStackedWidget *m_stackedWid;
    musicWidgets *m_musicWid;
    cameraWidgets *m_cameraWid;
    videoWidgets *m_videoWid;
    settingWidgets *m_settingwid;
    galleryWidgets *m_galleryWid;

    mainWidgetUp *m_mainwidup;
    mainWidgetLow *m_mainwidlow;

    QStackedLayout *m_mainlyout;     // 主界面的堆栈式布局，包含两个元素: m_mainwid和m_stackedwid

    // 进入具体板块的动画效果
    QPropertyAnimation *m_upwidclose;
    QPropertyAnimation *m_lowwidclose;
    QPropertyAnimation *m_upwidopen;
    QPropertyAnimation *m_lowwidopen;

    CWaitDialog *m_waitDialog;

    bool mediaHasUpdate;
protected:
    // 解决无边框窗口在最小化之后子控件不刷新的问题
    void showEvent(QShowEvent *e);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
private slots:
    void slot_appQuit();

    void slot_showEasyConnect();
    void slot_showSetting();
    void slot_showMusic();
    void slot_showVideo();
    void slot_showGallery();
    void slot_showCamera();
    void slot_closeCamera() {closeCameraApp();};
    void slot_closeanimationfinished();
    void slot_standby();
    void slot_updateMedia1();

    void slot_beginCarplay();
    void slot_beginEasyConnect();
    void slot_resetSiganls();
    void slot_showBeginCarplay();
public slots:
     void slot_updateMedia2();
    void slot_returnanimation();
    void slot_updateUiByRes(QFileInfoList musicFileList,QFileInfoList videoFileList,QMap<QString,QImage> imageRes);
signals:
    void beginUpdateMediaResource();
    void updateUiByRes(QFileInfoList musicFileList,QFileInfoList videoFileList,QMap<QString,QImage> imageRes);
};

class mediaUpdateThread:public QThread
{
public:
    mediaUpdateThread(QObject *parent ,mainWindow *mainWindow);
private:
    mainWindow *m_mainWindow;
protected:
    void run();
};


#endif // MAINWINDOW_H
