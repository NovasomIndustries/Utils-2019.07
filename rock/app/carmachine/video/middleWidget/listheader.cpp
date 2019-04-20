#include "listheader.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "global_value.h"

#ifdef DEVICE_EVB
int video_header_height = 70;
#else
int video_header_height = 40;
#endif
listHeader::listHeader(QWidget *parent):baseWidget(parent)
{
    initWidget();
    connect(m_button1,SIGNAL(buttonClick()),this,SLOT(slot_onButtonLocalClick()));
    connect(m_button2,SIGNAL(buttonClick()),this,SLOT(slot_onButtonNetClick()));
    m_button1->setFousedStyle();
}

void listHeader::initWidget()
{
    QHBoxLayout *hmainlyout = new QHBoxLayout;

    m_button1 = new funtionButton(str_listheader_local_video,this);
    m_button2 = new funtionButton(str_listheader_net_video,this);
    m_button1->setFixedHeight(video_header_height);
    m_button2->setFixedHeight(video_header_height);

    hmainlyout->addWidget(m_button1);
    hmainlyout->addWidget(m_button2);
    hmainlyout->setContentsMargins(0,0,0,0);
    hmainlyout->setSpacing(0);

    setLayout(hmainlyout);
}

void listHeader::slot_onButtonLocalClick()
{
    m_button2->removeFouseStyle();
    emit buttonLocalClick();
}

void listHeader::slot_onButtonNetClick()
{
    m_button1->removeFouseStyle();
    emit buttonNetClick();
}

funtionButton::funtionButton(QString title,QWidget *parent):baseWidget(parent)
{
    m_isCurItem = false;
    initWidget();
    m_title->setText(title);
}

void funtionButton::initWidget()
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    m_title = new QLabel("",this);
    QFont font = m_title->font();
    font.setPixelSize(font_size_big);
    font.setBold(true);
    m_title->setFont(font);
    m_title->setAlignment(Qt::AlignCenter);
    m_title->adjustSize();

    m_bottomLine=new QFrame(this);
    m_bottomLine->setFixedHeight(2);
    m_bottomLine->setStyleSheet("QFrame{border:1px solid rgb(100,100,100,255);}");
    m_bottomLine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    vmainlyout->addWidget(m_title);
    vmainlyout->addWidget(m_bottomLine);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(0);

    setLayout(vmainlyout);
}

void funtionButton::enterEvent(QEvent *)
{
    m_title->setStyleSheet("color:rgb(26,158,255);");
    update();
}

void funtionButton::leaveEvent(QEvent *)
{
    if(!m_isCurItem){
        m_title->setStyleSheet("color:rgb(255,255,255);");
        update();
    }
}

void funtionButton::mousePressEvent(QMouseEvent *event)
{
    if(!m_isCurItem && event->button()==Qt::LeftButton)
    {
        setFousedStyle();
        emit buttonClick();
    }
}

void funtionButton::removeFouseStyle()
{
    m_isCurItem = false;
    m_title->setStyleSheet("color:rgb(255,255,255);");
    m_bottomLine->setStyleSheet("QFrame{border:1px solid rgb(100,100,100,255);}");
    update();
}

void funtionButton::setFousedStyle()
{
    m_isCurItem = true;
    m_title->setStyleSheet("color:rgb(26,158,255);");
    m_bottomLine->setStyleSheet("QFrame{border:1px solid rgb(26,158,255);}");
    update();
}
