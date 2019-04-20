#include "videoquickcontentwidget.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QBitmap>
#include <QDesktopWidget>
#include <QApplication>

videoQuickContentWidget::videoQuickContentWidget(QWidget *parent):QQuickWidget(parent)
{
    init();

    // 初始化定时器，主要为了区分单击和双击事件
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onOneClick()));
}

void videoQuickContentWidget::init()
{
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setAutoFillBackground(true);
    setWindowOpacity(1);           //设置透明度
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAcceptDrops(true);    //设置可以接受拖拽
}

void videoQuickContentWidget::mousePressEvent(QMouseEvent *){
    m_timer->start(300);
}

void videoQuickContentWidget::mouseDoubleClickEvent(QMouseEvent *){
    m_timer->stop();
    emit contentDoubleClick();
}

void videoQuickContentWidget::onOneClick(){
    m_timer->stop();
    emit contentOneClick();
}

void videoQuickContentWidget::setFullScreen(bool fullScreen)
{
    if(fullScreen){
        normalWidth = this->width();
        normalHeight=this->height();
        this->setFixedSize(QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height());
    }else{
        this->setFixedSize(normalWidth,normalHeight);
    }
}


