#include "middlewidgetleft.h"

#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>
#include <QDebug>
#include <QTimer>
#include "global_value.h"

#ifdef DEVICE_EVB
    int tabIcon_size = 80;
    QString music_tabIcon_res_str_1 = ":/image/music/btn_music (1)_big.png";
    QString music_tabIcon_res_str_2 = ":/image/music/btn_music (2)_big.png";
    QString music_tabIcon_res_str_3 = ":/image/music/btn_music (3)_big.png";
    QString cloud_tabIcon_res_str_1 = ":/image/music/btn_cloud (1)_big.png";
    QString cloud_tabIcon_res_str_2 = ":/image/music/btn_cloud (2)_big.png";
    QString cloud_tabIcon_res_str_3 = ":/image/music/btn_cloud (3)_big.png";
    QString radio_tabIcon_res_str_1 = ":/image/music/btn_radio (1)_big.png";
    QString radio_tabIcon_res_str_2 = ":/image/music/btn_radio (2)_big.png";
    QString radio_tabIcon_res_str_3 = ":/image/music/btn_radio (3)_big.png";
#else
    int tabIcon_size = 40;
    QString music_tabIcon_res_str_1 = ":/image/music/btn_music (1).png";
    QString music_tabIcon_res_str_2 = ":/image/music/btn_music (2).png";
    QString music_tabIcon_res_str_3 = ":/image/music/btn_music (3).png";
    QString cloud_tabIcon_res_str_1 = ":/image/music/btn_cloud (1).png";
    QString cloud_tabIcon_res_str_2 = ":/image/music/btn_cloud (2).png";
    QString cloud_tabIcon_res_str_3 = ":/image/music/btn_cloud (3).png";
    QString radio_tabIcon_res_str_1 = ":/image/music/btn_radio (1).png";
    QString radio_tabIcon_res_str_2 = ":/image/music/btn_radio (2).png";
    QString radio_tabIcon_res_str_3 = ":/image/music/btn_radio (3).png";
#endif

QColor middleWidgetLeft::color=QColor(230,230,230);
QColor middleWidgetLeft::bgcolor=QColor(255,255,255,100);

middleWidgetLeft::middleWidgetLeft(QWidget *parent):baseWidget(parent)
{
    m_isDrawVerticalLine=true;
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);

    initLayout();
    initAnimation();
}

void middleWidgetLeft::initLayout()
{
    QVBoxLayout *vlyout=new QVBoxLayout;

    m_stackwid=new QStackedWidget(this);
    m_stackwid->setFrameShadow(QFrame::Plain);
    m_stackwid->setFrameShape(QFrame::NoFrame);

    m_Swidget0=new middleLeftStackWidget0(this);
    m_Swidget1=new middleLeftStackWidget1(this);
    m_Swidget2=new middleLeftStackWidget2(this);

    m_stackwid->addWidget(m_Swidget0);
    m_stackwid->addWidget(m_Swidget1);
    m_stackwid->addWidget(m_Swidget2);

    m_stackwid->setContentsMargins(0,0,0,0);

    m_btn[0]=new stackButton(music_tabIcon_res_str_1,music_tabIcon_res_str_2,music_tabIcon_res_str_3,this);
    m_btn[1]=new stackButton(cloud_tabIcon_res_str_1,cloud_tabIcon_res_str_2,cloud_tabIcon_res_str_3,this);
    m_btn[2]=new stackButton(radio_tabIcon_res_str_1,radio_tabIcon_res_str_2,radio_tabIcon_res_str_3,this);

    m_btn[0]->setFixedHeight(tabIcon_size);
    m_btn[1]->setFixedHeight(tabIcon_size);
    m_btn[2]->setFixedHeight(tabIcon_size);

    QHBoxLayout *hlyout=new QHBoxLayout;
    hlyout->addWidget(m_btn[0]);
    hlyout->addWidget(m_btn[1]);
    hlyout->addWidget(m_btn[2]);
    hlyout->setContentsMargins(0,0,0,0);
    hlyout->setSpacing(0);

    vlyout->addLayout(hlyout);
    vlyout->addWidget(m_stackwid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);

    for(int i=0;i<3;i++)
    {
        m_btn[i]->setObjectName(QString::number(i));
        connect(m_btn[i],SIGNAL(pressed()),this,SLOT(slot_btn()));
    }

    connect(m_stackwid,SIGNAL(currentChanged(int)),this,SLOT(slot_changeButtonSelected(int)));

    m_stackwid->setCurrentIndex(0);//选中第一个stackwidget
    m_btn[0]->setselected(true); //设置
}

// stackedWidget的界面改变之后更改上方导航按钮的样式与切换stackedWidget
void middleWidgetLeft::slot_changeButtonSelected(int index)
{
    m_isAnima=true;
    m_index=index;
    m_animation->setStartValue(m_preindex*m_btn[0]->width());
    m_animation->setEndValue(index*m_btn[0]->width());
    m_animation->start();

    for(int i=0;i<5;i++)
    {
        if(i==index)
        {
            m_btn[index]->setselected(true);
        }
        else
        {
            m_btn[i]->setselected(false);
        }
    }

    if(index>m_preItem)
    {
        m_Widanimation->setTargetObject(m_stackwid);
        m_Widanimation->setStartValue(QRect(m_stackwid->width(),tabIcon_size,m_stackwid->width(),m_stackwid->height()));
        m_Widanimation->setEndValue(QRect(0,tabIcon_size,m_stackwid->width(),m_stackwid->height()));
        m_Widanimation->start();
    }
    if(index<m_preItem)
    {
        m_Widanimation->setTargetObject(m_stackwid);
        m_Widanimation->setStartValue(QRect(-m_stackwid->width(),tabIcon_size,m_stackwid->width(),m_stackwid->height()));
        m_Widanimation->setEndValue(QRect(0,tabIcon_size,m_stackwid->width(),m_stackwid->height()));
        m_Widanimation->start();
    }
    m_preItem=index;
}

void middleWidgetLeft::initAnimation()
{
    m_pix=QPixmap(":/image/music/indicator.png");
    m_index=-1;
    m_preindex=-1;
    m_preItem=0;
    m_x=0;
    m_isAnima=true;
    m_animation=new QPropertyAnimation(this,"m_x");
    m_animation->setDuration(200);

    m_stackwid->setCurrentIndex(0);
    connect(m_animation,SIGNAL(finished()),this,SLOT(slot_finished()));

    m_Widanimation=new QPropertyAnimation(this,"geometry");
    m_Widanimation->setTargetObject(m_stackwid);
    m_Widanimation->setDuration(200);
}

void middleWidgetLeft::setBackgroundtransparent()
{
    color=QColor(55,55,55,55);
    setDrawVerticalLine(false);
    update();
}

void middleWidgetLeft::setBackgroundnormal()
{
    color=QColor(230,230,230);
    setDrawVerticalLine(true);
    update();
}
void middleWidgetLeft::setWidgetOpacity(int value)
{
    middleWidgetLeft::bgcolor=QColor(255,255,255,value);
    update();
}

void middleWidgetLeft::setInitMainWidgets(musicWidgets *musicWidgets)
{
    this->m_mainWid = musicWidgets;
    this->m_Swidget0->setInitMainWidgets(m_mainWid);
}

void middleWidgetLeft::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::transparent);
    p.setBrush(bgcolor);//刷透明区域
    p.drawRect(-1,-1,width(),height()+1);
    p.setPen(color);

    if(m_isAnima)
    {
        if(m_isDrawVerticalLine)
            p.drawLine(width()-1,0,width()-1,height());//vertical line
        p.drawLine(0,m_btn[0]->y()+m_btn[0]->height()-1,m_x+(m_btn[0]->width()-m_pix.width())/2-1,m_btn[0]->y()+m_btn[0]->height()-1);//first line
        p.drawLine(m_x+(m_btn[0]->width()-m_pix.width())/2+m_pix.width(),m_btn[0]->y()+m_btn[0]->height()-1,width(),m_btn[0]->y()+m_btn[0]->height()-1);//second line
        p.drawPixmap(m_x+(m_btn[0]->width()-m_pix.width())/2,m_btn[0]->y()+m_btn[0]->height()-m_pix.height()+1,m_pix);
    }
    else
    {
        if(m_isDrawVerticalLine)
            p.drawLine(width()-1,0,width()-1,height());

        p.drawLine(0,m_btn[0]->y()+m_btn[0]->height()-1,m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2-1,m_btn[0]->y()+m_btn[0]->height()-1);
        p.drawLine(m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2+m_pix.width(),m_btn[0]->y()+m_btn[0]->height()-1,width(),m_btn[0]->y()+m_btn[0]->height()-1);
        p.drawPixmap(m_index*m_btn[0]->width()+(m_btn[0]->width()-m_pix.width())/2,m_btn[0]->y()+m_btn[0]->height()-m_pix.height()+1,m_pix);
    }
}


void middleWidgetLeft::slot_btn()
{
    m_preindex=m_stackwid->currentIndex();
    m_stackwid->setCurrentIndex(sender()->objectName().toInt());
}

void middleWidgetLeft::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}
