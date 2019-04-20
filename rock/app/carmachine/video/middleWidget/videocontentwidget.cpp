#include "videocontentwidget.h"
#include <QMouseEvent>
#include <QMimeData>
#include <QBitmap>

videoContentWidget::videoContentWidget(QWidget *parent):QVideoWidget(parent)
{
    init();

    // 初始化定时器，主要为了区分单击和双击事件
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onOneClick()));
}

void videoContentWidget::init()
{
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setAutoFillBackground(true);
    setWindowOpacity(1);           //设置透明度
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAcceptDrops(true);    //设置可以接受拖拽
}

void videoContentWidget::mousePressEvent(QMouseEvent *){
    m_timer->start(300);
}

void videoContentWidget::mouseDoubleClickEvent(QMouseEvent *){
    m_timer->stop();
    emit contentDoubleClick();
}

void videoContentWidget::onOneClick(){
    m_timer->stop();
    emit contentOneClick();
}

