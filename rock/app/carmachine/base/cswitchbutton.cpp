#include "cswitchbutton.h"

CSwitchButton::CSwitchButton(QWidget *parent): QWidget(parent)
{
    setMouseTracking(true);
    //OFF背景色
    m_offbkcolor1       = QColor(227, 227, 227);
    m_offbkcolor2       = QColor(227, 227, 227);
    //ON背景色
    m_onbkcolor1        = QColor(85, 180, 238);
    m_onbkcolor2        = QColor(30,125,183);
    //滑块背景色
    m_slidecolor1       = QColor(252, 252, 252);
    m_slidecolor2       = QColor(224, 224, 224);
    //开关状态
    m_state             = false;
    m_mouseDown         = false;
    m_mouseMove         = false;
    m_mouseUp           = true;
}

void CSwitchButton::setChecked(bool state)
{
    if(m_state!=state)
    {
        m_state = state;
        repaint();
    }
}

void CSwitchButton::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        m_mouseDown = true;
        m_mouseUp = false;
        firstPoint = event->pos();
    }
}

void CSwitchButton::mouseMoveEvent(QMouseEvent * event)
{
    if(m_mouseDown)
    {
        m_mouseMove = true;
        lastPoint = event->pos(); //获取当前光标的位置
        repaint();
    }
}

void CSwitchButton::mouseReleaseEvent(QMouseEvent * event)
{
    if(m_mouseDown) {
        m_mouseDown = false;
        m_mouseMove = false;
        m_mouseUp = true;
        if (event->pos().x() < width() / 2.0)
        {
            if(m_state!=false)
            {
                emit checkStateChanged(false);
                m_state = false;
            }
        }
        else
        {
            if(m_state!=true)
            {
                emit checkStateChanged(true);
                m_state = true;
            }
        }
        repaint();
    }
}

void CSwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿
    drawPressBackground(&painter);
    if(m_mouseMove) {
        QRect sliderect;
        int left;
        int diff = lastPoint.x()-firstPoint.x(); //计算移动差值
        if(m_state) {
            //(width() -  height() + 4 - 2) --- 表示滑块右边界值
            left = (width() -  height() + 4 - 2) + diff;
            if(left < 2) {
                sliderect.setLeft(2);
            }
            else if (left > (width() -  height() + 4 - 2)) {
                sliderect.setLeft(width() -  height() + 4 - 2);
            }
            else {
                sliderect.setLeft(width() -  height() + 4 - 2 + diff);
            }
        }
        else {
            left = diff;
            if(left < 2) {
                sliderect.setLeft(2);
            }
            else if (left > (width() -  height() + 4 - 2)) {
                sliderect.setLeft(width() -  height() + 4 - 2);
            }
            else {
                sliderect.setLeft(diff);
            }
        }
        sliderect.setTop(2);
        sliderect.setWidth(height() - 4 );
        sliderect.setHeight(height() - 4);

        painter.setPen(Qt::NoPen);
        QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
        linGrad.setColorAt(0, m_slidecolor1);
        linGrad.setColorAt(1, m_slidecolor2);
        linGrad.setSpread(QGradient::PadSpread);
        painter.setBrush(linGrad);

        QRect rrect = sliderect.intersected(rect());
        painter.drawEllipse(rrect);
        //画边框
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(173, 173, 173, 160));
        painter.drawEllipse(rrect);
    }
    else {
        drawPressSlide(&painter);
    }
}
//画背景
void CSwitchButton::drawPressBackground(QPainter *painter)
{
    QPainterPath path;

    path.moveTo(height() / 2.0, 0);
    path.arcTo(QRectF(0, 0, height(), height()), 90, 180);
    path.lineTo(width() - height() / 2.0, height());
    path.arcTo(QRectF(width() - height(), 0, height(), height()), 270, 180);
    path.lineTo(height() / 2.0, 0);

    QPainterPath pathrect;
    pathrect.moveTo(0, 0);
    pathrect.lineTo(0, height());
    pathrect.lineTo(width(), height());
    pathrect.lineTo(width(), 0);
    pathrect.lineTo(0, 0);

    QPainterPath interpath = path.intersected(pathrect);
    painter->setPen(Qt::NoPen);
    QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
    linGrad.setColorAt(0, m_state ? m_onbkcolor1 : m_offbkcolor1);
    linGrad.setColorAt(1, m_state ? m_onbkcolor2 : m_offbkcolor2);

    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);
    painter->drawPath(interpath);
    //画边框
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor(173, 173, 173, 255));
    painter->drawPath(interpath);
}

//画滑块
void CSwitchButton::drawPressSlide(QPainter *painter)
{
    QRect sliderect;
    sliderect.setLeft(m_state ? width() -  height() + 4 - 2 : 2);
    sliderect.setTop(2);
    sliderect.setWidth(height() - 4 );
    sliderect.setHeight(height() - 4);

    painter->setPen(Qt::NoPen);
    QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
    linGrad.setColorAt(0, m_slidecolor1);
    linGrad.setColorAt(1, m_slidecolor2);
    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);
    QRect rrect = sliderect.intersected(rect());
    painter->drawEllipse(rrect);
    //画边框
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor(173, 173, 173, 160));
    painter->drawEllipse(rrect);
}
