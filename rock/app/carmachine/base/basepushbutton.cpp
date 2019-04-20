#include "basepushbutton.h"
#include <QPainter>

/*----------------------扁平按钮-----------------------------*/
flatButton::flatButton(QWidget*parent):QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);   // 设置为水平状态，默认为突出
    setStyleSheet("QPushButton{background:transparent;}");
}

flatButton::flatButton(const QString& str, QWidget *parent):QPushButton(str,parent)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);   // 设置为水平状态，默认为突出
    setStyleSheet("QPushButton{background:transparent;}");
}
/*------------------------------------------------------------*/
/*---------------------音乐音量按钮-------------------------------*/
volButton::volButton(const QString& normal,QWidget*parent):QPushButton(parent)//5个连一串
{
    m_partnerslider=NULL;
    m_isenter=false;
    m_index=0;
    m_isvolempty=100;
    m_savevol=100;
    setCursor(Qt::PointingHandCursor);

    QPixmap pix(normal);

    for(int i=0;i<5;i++)
        m_listnormal<<pix.copy(i*(pix.width()/5),0,pix.width()/5,pix.height());

}

void volButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap((width()-m_listnormal.at(0).width())/2,(height()-m_listnormal.at(0).height())/2,m_listnormal.at(m_index));
}

void volButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        QPushButton::mousePressEvent(e);
    }
}

void volButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        if(this->contentsRect().contains(mapFromGlobal(QCursor::pos())))
        {
            if(m_isvolempty==0)//如果没有音量就 设置一个
            {
                emit setMute(m_savevol);
            }
            else//如果有音量 设置音量为0;
            {
                m_savevol=m_partnerslider->value();
                emit setMute(0);
            }
        }
        QPushButton::mouseReleaseEvent(e);
    }
}

void volButton::setButtonPixmap(int value)
{
    m_isenter=false;
    if(value==0)
        m_index=4;
    if(value>2&&value<=30)
        m_index=1;
    if(value>30)
        m_index=2;
    update();
    m_isvolempty=value;//判断值为0;
}

void volButton::enterEvent(QEvent *)
{
    m_isenter=true;
    update();
}

void volButton::leaveEvent(QEvent *)
{
    m_isenter=false;
    update();
}
/*------------------------------------------------------------*/
/*--------------------stack button-----------------------------------*/
stackButton::stackButton(const QString& pixnormal,const QString& pixhover,const QString& pixsel,QWidget*parent):QPushButton(parent)
{
    m_enter=false;
    m_pressed=false;
    m_pixnormal=QPixmap(pixnormal);
    m_pixhover=QPixmap(pixhover);
    m_pixselected=QPixmap(pixsel);
    setCursor(Qt::PointingHandCursor);
    setFlat(true);
}

void stackButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter p(this);
    if(!m_enter&&!m_pressed)//初始化
        p.drawPixmap((width()-m_pixnormal.width())/2,(height()-m_pixnormal.height())/2,m_pixnormal);

    if(m_enter&&!m_pressed)//未选中进入
        p.drawPixmap((width()-m_pixhover.width())/2,(height()-m_pixhover.height())/2,m_pixhover);

    if(m_pressed)//选中
        p.drawPixmap((width()-m_pixselected.width())/2,(height()-m_pixselected.height())/2,m_pixselected);

}

void stackButton::setselected(bool sel)//用于控制pix显示
{
    m_pressed=sel;
    update();
}

void stackButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(e->button()==Qt::LeftButton)
    {
        m_pressed=true;
        update();
    }
}

void stackButton::enterEvent(QEvent *e)
{
    QPushButton::enterEvent(e);
    m_enter=true;
    update();
}

void stackButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    m_enter=false;
    update();
}
/*------------------------------------------------------------*/

/*----------------主界面 导航按钮(Music、Video。。)---------------*/
guideButton::guideButton(QString pixnormal, QString text, QWidget *parent):QPushButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-image: url("+pixnormal+");");
    m_pix=QPixmap(pixnormal);
    m_text=text;
    m_enter = false;
}


//void guideButton::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);

//    painter.drawPixmap(QRect((rect().width()-m_pix.width())/2,(rect().height()-m_pix.height())/3,m_pix.width(),m_pix.height()),m_pix);

//    QFontMetrics fontmetr(QFont("微软雅黑", 9, QFont::Normal));
//    int m_width= fontmetr.width(m_text);

//    painter.setPen(QColor(255, 255, 255));
//    painter.setFont(QFont("微软雅黑", 9, QFont::Normal));
//    painter.drawText(QPoint((rect().width()-m_width)/2,(rect().height()-m_pix.height())/3+m_pix.height()+20),m_text);

//绘制菜单按钮
//    if(m_enter)
//        drawMenuButton(&painter);
//}


void guideButton::enterEvent(QEvent *)
{
    m_enter = true;
    update();
}
void guideButton::leaveEvent(QEvent *)
{
    m_enter = false;
    update();
}
/*------------------------------------------------------------*/

/*----------------4态图标-------------------------*/
FourStateButton::FourStateButton(QString pixnormal,QWidget *parent):QPushButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    m_index=0;
    m_enter=false;
    QPixmap pix(pixnormal);
    for(int i=0;i<4;i++)
        m_pixlist<<pix.copy(i*(pix.width()/4),0,pix.width()/4,pix.height());
}

void FourStateButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap((width()-m_pixlist.at(m_index).width())/2,(height()-m_pixlist.at(m_index).height())/2
                       ,m_pixlist.at(m_index).width()
                       ,m_pixlist.at(m_index).height(),m_pixlist.at(m_index));//画图画到中间
}

void FourStateButton::enterEvent(QEvent *)
{
    m_index=1;
    m_enter=true;
    update();
}

void FourStateButton::leaveEvent(QEvent *)
{
    m_index=0;
    m_enter=false;
    update();
}
void FourStateButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)//如果是左键按下
    {
        m_index=2;
        update();
        QPushButton::mousePressEvent(e);//返回到上级
    }

}
void FourStateButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)//如果是左键放下
    {
        m_index=1;
        update();
        QPushButton::mouseReleaseEvent(e);//返回到上级 引出按钮clicked信号
    }
}
/*------------------------------------------------------------*/
