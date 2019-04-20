#include "mainwindow.h"
#include <global_value.h>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <stdlib.h>
#include <QFileDialog>
#include <QProcess>

#include "qprogressindicator.h"
#include "PowerManager.h"
mainWindow::mainWindow(QWidget *parent):baseWindow(parent)
  ,mediaHasUpdate(false)
{
    initLayout();
    initAnimation();
    initConnection();
    mainwid = this;
    slot_updateMedia2();
}

void mainWindow::initLayout()
{
    m_mainwidup = new mainWidgetUp(m_mainwid);
    m_mainwidlow = new mainWidgetLow(m_mainwid);
    QVBoxLayout *vlyout=new QVBoxLayout;  // m_mainwid's layout(total)
    vlyout->addWidget(m_mainwidup,3);
    vlyout->addWidget(m_mainwidlow,1);
    vlyout->setContentsMargins(0,0,0,0);
    m_mainwid->setLayout(vlyout);

    m_stackedWid = new QStackedWidget(this);
    m_settingwid = new settingWidgets(m_stackedWid);
    m_musicWid  = new musicWidgets(m_stackedWid);
    m_cameraWid = new cameraWidgets(m_stackedWid);
    m_videoWid = new videoWidgets(m_stackedWid);
    m_galleryWid = new galleryWidgets(m_stackedWid,this);

    m_stackedWid->addWidget(m_settingwid);
    m_stackedWid->addWidget(m_musicWid);
    m_stackedWid->addWidget(m_videoWid);
    m_stackedWid->addWidget(m_galleryWid);
    m_stackedWid->addWidget(m_cameraWid);

    m_mainlyout=new QStackedLayout;
    m_mainlyout->addWidget(m_mainwid);
    m_mainlyout->addWidget(m_stackedWid);

    m_mainlyout->setContentsMargins(0,0,0,0);
    setLayout(m_mainlyout);

    m_mainlyout->setCurrentWidget(m_mainwid);

    m_waitDialog = new CWaitDialog("EasyConnect Start",this);
    m_waitDialog->hide();
}

void mainWindow::initConnection()
{
    connect(m_mainwidup->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_mainwidup->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));

    connect(m_settingwid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_settingwid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_musicWid->m_topwid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_musicWid->m_topwid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_cameraWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_cameraWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_cameraWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_closeCamera()));
    connect(m_videoWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_videoWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
    connect(m_galleryWid->m_topWid->m_btnmini,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_galleryWid->m_topWid->m_btnexit,SIGNAL(clicked(bool)),this,SLOT(slot_appQuit()));
#ifndef DEVICE_EVB
    connect(m_mainwidlow->m_btnEasyConnect,SIGNAL(clicked(bool)),this,SLOT(slot_showEasyConnect()));
    connect(m_mainwidlow->m_btnCarplay,SIGNAL(clicked(bool)),this,SLOT(slot_beginCarplay()));
#endif
    connect(m_mainwidlow->m_btnSetUp,SIGNAL(clicked(bool)),this,SLOT(slot_showSetting()));
    connect(m_mainwidlow->m_btnMusic,SIGNAL(clicked(bool)),this,SLOT(slot_showMusic()));
    connect(m_mainwidlow->m_btnVideo,SIGNAL(clicked(bool)),this,SLOT(slot_showVideo()));
    connect(m_mainwidlow->m_btnGallery,SIGNAL(clicked(bool)),this,SLOT(slot_showGallery()));
    connect(m_mainwidlow->m_btnCamera,SIGNAL(clicked(bool)),this,SLOT(slot_showCamera()));

    connect(m_upwidclose,SIGNAL(finished()),this,SLOT(slot_closeanimationfinished()));
    connect(m_lowwidclose,SIGNAL(finished()),this,SLOT(slot_closeanimationfinished()));

    connect(m_musicWid->m_topwid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    connect(m_cameraWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
//    connect(m_videoWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    //    connect(m_galleryWid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));
    connect(m_settingwid->m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_returnanimation()));

    connect(this,SIGNAL(beginUpdateMediaResource()),this,SLOT(slot_updateMedia1()));
    connect(this,SIGNAL(updateUiByRes(QFileInfoList,QFileInfoList,QMap<QString,QImage>)),this,SLOT(slot_updateUiByRes(QFileInfoList,QFileInfoList,QMap<QString,QImage>)));
}

void mainWindow::slot_appQuit()
{
    m_musicWid->savaSetting();
    m_videoWid->savaSetting();
    this->close();
}

void mainWindow::initAnimation()
{
    // initialize the animation,and position change realize in resize()
    m_upwidclose=new QPropertyAnimation(m_mainwidup,"pos");
    m_lowwidclose=new QPropertyAnimation(m_mainwidlow,"pos");
    m_upwidopen=new QPropertyAnimation(m_mainwidup,"pos");
    m_lowwidopen=new QPropertyAnimation(m_mainwidlow,"pos");
}


void mainWindow::slot_showEasyConnect()
{  
    qDebug()<<"Easy Connect begin.";
    m_waitDialog->show();
    QTimer::singleShot(10,this,SLOT(slot_beginEasyConnect()));
}

void mainWindow::slot_beginCarplay()
{
    this->setWindowOpacity(0);
    QTimer::singleShot(10,this,SLOT(slot_showBeginCarplay()));
}

void mainWindow::slot_showBeginCarplay(){
    qDebug()<<"slot_showBeginCarplay begin...";
    QProcess *process = new QProcess(this);
    system("/bin/z-link.sh");
    process->execute("/bin/z-link");
    system("/bin/unz-link.sh");
    setWindowOpacity(1);
    qDebug()<<"slot_showBeginCarplay end...";
}

void mainWindow::slot_beginEasyConnect()
{
#ifndef DEVICE_EVB
    m_mainwidlow->m_btnEasyConnect->blockSignals(true);
    m_mainwidlow->m_btnCarplay->blockSignals(true);
#endif
    m_mainwidlow->m_btnSetUp->blockSignals(true);
    m_mainwidlow->m_btnMusic->blockSignals(true);
    m_mainwidlow->m_btnVideo->blockSignals(true);
    m_mainwidlow->m_btnGallery->blockSignals(true);
    m_mainwidlow->m_btnCamera->blockSignals(true);
    QProcess *process = new QProcess(this);
     if(QFile::exists("/data/"))
    {
	qDebug()<<"Easy Connect /data";
    process->execute("/usr/bin/EasyConnect/EasyConnected.RXW01.Linux -platform EGLFS -l 0 -s 83991906 -p /data");
    //    process->execute("./mnt/EasyConnect/run.sh");
    }else{
	process->execute("/usr/bin/EasyConnect/EasyConnected.RXW01.Linux -platform EGLFS -l 0 -s 83991906 -p /usr/share");

     	}
    m_waitDialog->hide();
    qDebug()<<"Easy Connect end";

    QTimer::singleShot(1000,this,SLOT(slot_resetSiganls()));
}

void mainWindow::slot_resetSiganls()
{
#ifndef DEVICE_EVB
    m_mainwidlow->m_btnEasyConnect->blockSignals(false);
    m_mainwidlow->m_btnCarplay->blockSignals(false);
#endif
    m_mainwidlow->m_btnSetUp->blockSignals(false);
    m_mainwidlow->m_btnMusic->blockSignals(false);
    m_mainwidlow->m_btnVideo->blockSignals(false);
    m_mainwidlow->m_btnGallery->blockSignals(false);
    m_mainwidlow->m_btnCamera->blockSignals(false);
}

void mainWindow::slot_showSetting()
{
    m_stackedWid->setCurrentIndex(0);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showMusic()
{
    m_stackedWid->setCurrentIndex(1);
    m_upwidclose->start();
    m_lowwidclose->start();

}

void mainWindow::slot_showVideo()
{
    m_stackedWid->setCurrentIndex(2);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showGallery()
{
    m_stackedWid->setCurrentIndex(3);
    m_upwidclose->start();
    m_lowwidclose->start();
}

void mainWindow::slot_showCamera()
{
    qDebug() << "slot_showCamera";
    m_stackedWid->setCurrentIndex(4);
    m_upwidclose->start();
    m_lowwidclose->start();
    //m_cameraWid->openCamera();
}

void mainWindow::slot_returnanimation()
{
    m_mainlyout->setCurrentWidget(m_mainwid);
    m_upwidopen->start();
    m_lowwidopen->start();
}

void mainWindow::slot_closeanimationfinished()
{
    m_mainlyout->setCurrentWidget(m_stackedWid);
}

void mainWindow::slot_updateMedia1()
{
    if(!mediaHasUpdate)
    {
        mediaHasUpdate = true;
        QTimer::singleShot(2000,this,SLOT(slot_updateMedia2()));
    }
}

void mainWindow::slot_updateMedia2()
{
    qDebug()<<"Carmachine: Update media resource.";
    mediaUpdateThread *thread = new mediaUpdateThread(this,this);
    thread->start();
    mediaHasUpdate =false;
}

void mainWindow::slot_updateUiByRes(QFileInfoList musicFileList,QFileInfoList videoFileList,QMap<QString,QImage> imageRes)
{
    m_musicWid->m_middlewid->m_leftWid->m_Swidget0->updateResUi(musicFileList);
    m_videoWid->m_middleWid->m_rightWid->updateResUi(videoFileList);
    m_galleryWid->m_middleWid->updateResUi(imageRes);
    if(m_videoWid->getPlayer()->currentMedia().canonicalUrl().toString()!="")
    {
        m_videoWid->slot_onCurrentMediaChanged(m_videoWid->getPlayer()->currentMedia());
    }
    if(m_musicWid->getPlayer()->currentMedia().canonicalUrl().toString()!="")
    {
        m_musicWid->slot_onCurrentMediaChanged(m_musicWid->getPlayer()->currentMedia());
    }
}

void mainWindow::showEvent(QShowEvent *e)
{
    // slove window not update after animation.
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(e);
}

void mainWindow::resizeEvent(QResizeEvent*)
{
    m_upwidclose->setStartValue(QPoint(0,0));
    m_upwidclose->setEndValue(QPoint(0,-m_mainwid->height()/4*3));
    m_upwidclose->setDuration(500);

    m_upwidopen->setStartValue(QPoint(0,-m_mainwid->height()/4*3));
    m_upwidopen->setEndValue(QPoint(0,0));
    m_upwidopen->setDuration(500);

    m_lowwidclose->setStartValue(QPoint(0,m_mainwid->height()/4*3));
    m_lowwidclose->setEndValue(QPoint(0,m_mainwid->height()));
    m_lowwidclose->setDuration(500);

    m_lowwidopen->setStartValue(QPoint(0,m_mainwid->height()));
    m_lowwidopen->setEndValue(QPoint(0,m_mainwid->height()/4*3));
    m_lowwidopen->setDuration(500);
}

void mainWindow::slot_standby()
{
    system("echo mem > /sys/power/state");
}


void mainWindow::closeCameraApp()
{
    qDebug() << "closeCameraApp";
    m_cameraWid->closeCamera();
}

void mainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"key value is:"<<event->key();
    switch(event->key())
    {
    // update musicPlayer and videoPlayer's volume by Key
    case Qt::Key_VolumeDown:
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->updateVolume(false);;
        }else if(m_stackedWid->currentWidget()==m_musicWid){
            m_musicWid->updateVolume(false);
        }
        QWidget::keyPressEvent(event);
        break;
    case Qt::Key_VolumeUp:
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->updateVolume(true);
        }else if(m_stackedWid->currentWidget()==m_musicWid){
            m_musicWid->updateVolume(true);
        }
        QWidget::keyPressEvent(event);
        break;
    case Qt::Key_PowerOff:   // when key_power enter
    	qDebug()<<"key value is PowerKey "<<event->key();
		qDebug()<<"Screen Status is "<<rk_get_screen_status();
        if(m_stackedWid->currentWidget()==m_videoWid){
            m_videoWid->setPlayerPause();
        }

		if(rk_get_screen_status())
		{
			qDebug()<<"key value is PowerKey, screen off ";
			rk_screen_off();
			QTimer::singleShot(100, this, SLOT(slot_standby()));
		}
		else
		{
			qDebug()<<"key value is PowerKey, screen ON ";
			rk_screen_on();
		}
        break;
    default:
        break;
    }
}

mediaUpdateThread::mediaUpdateThread(QObject *parent,mainWindow *mainWindow):QThread(parent)
{
    m_mainWindow = mainWindow;
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    qRegisterMetaType<QMap<QString,QImage>>("QMap<QString,QImage>");
}

void mediaUpdateThread::run()
{
    QFileInfoList musicFileList = m_mainWindow->m_musicWid->m_middlewid->m_leftWid->m_Swidget0->findMusicFiles(MUSIC_SEARCH_PATH);
    QFileInfoList videoFileList = m_mainWindow->m_videoWid->m_middleWid->m_rightWid->findVideoFiles(VIDEO_SEARCH_PATH);
    QMap<QString,QImage> imageRes = m_mainWindow->m_galleryWid->m_middleWid->getImageResFromPath(MUSIC_SEARCH_PATH);
    emit m_mainWindow->updateUiByRes(musicFileList,videoFileList,imageRes);
}
