#include "playmodewidget.h"
#include <QVBoxLayout>
#include <QPainter>
#include <global_value.h>


playModeWidget::playModeWidget(QWidget *parent):baseWidget(parent)
{
    setStyleSheet("QWidget{background-color:rgb(64,64,64,200);border-radius:5px;}");
    setFixedSize(100,150);
    init();
}

void  playModeWidget::init()
{
    QVBoxLayout *vlyout=new QVBoxLayout;
    m_btnOrder=new playModeButton(":/image/music/btn_listcircle (1).png",":/image/music/btn_listcircle (2).png",str_playmode_list,this);
    m_btnRandom=new playModeButton(":/image/music/btn_listrandom (1).png",":/image/music/btn_listrandom (2).png",str_playmode_random,this);
    m_btnOneCircle=new playModeButton(":/image/music/btn_listscircle_single (1).png",":/image/music/btn_listscircle_single (2).png",str_playmode_single,this);
    m_btnOrder->setPlayMode(PlayMode::playInOrder);
    m_btnRandom->setPlayMode(PlayMode::playRandom);
    m_btnOneCircle->setPlayMode(PlayMode::playOneCircle);

    vlyout->addWidget(m_btnOrder);
    vlyout->addWidget(m_btnRandom);
    vlyout->addWidget(m_btnOneCircle);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);

    m_vector<<m_btnOrder<<m_btnRandom<<m_btnOneCircle;

    connect(m_btnOrder,SIGNAL(clicked(bool)),this,SLOT(slot_setCurrentMode()));
    connect(m_btnRandom,SIGNAL(clicked(bool)),this,SLOT(slot_setCurrentMode()));
    connect(m_btnOneCircle,SIGNAL(clicked(bool)),this,SLOT(slot_setCurrentMode()));
}

void playModeWidget::setCurrentMode(PlayMode mode)
{
    for(int i=0;i<m_vector.size();i++)
    {
        if(mode==m_vector.value(i)->playMode())
        {
            m_vector.value(i)->setCheckedBtn(true);
        }
        else
        {
            m_vector.value(i)->setCheckedBtn(false);
        }
    }
    emit sig_CurrentModeChange(mode);
}

void playModeWidget::slot_setCurrentMode()
{
    playModeButton*btn=(playModeButton*)sender();
    setCurrentMode(btn->playMode());
}





playModeButton::playModeButton(QString pixnormal, QString pixhover, QString text,QWidget *parent):QPushButton(parent)
{
    m_mode=PlayMode::playInOrder;
    setStyleSheet("background:transparent;");
    m_pixnormal=QPixmap(pixnormal);
    m_pixhover=QPixmap(pixhover);
    m_enter=false;
    m_pressed=false;
    m_text=text;
    setFixedSize(100,20);
    setCheckedBtn(false);
}

void playModeButton::enterEvent(QEvent *e)
{
    QPushButton::enterEvent(e);
    m_enter=true;
    update();
}
void playModeButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    //  m_pressed=true;
    //  update();
}

void playModeButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    m_enter=false;
    update();
}

void playModeButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::gray);
    p.drawPixmap(10,2,m_pixnormal);//16*16
    p.drawText(35,15,m_text);
    if(m_pressed||m_enter)
    {
        p.setPen(Qt::white);
        p.drawPixmap(10,2,m_pixhover);
        p.drawText(35,15,m_text);
    }

}
void playModeButton::setCheckedBtn(bool check)
{
    m_pressed=check;
    update();
}
