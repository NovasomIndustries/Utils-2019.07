#ifndef SWITCHCONTROL_H
#define SWITCHCONTROL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class CSwitchButton:public QWidget
{
    Q_OBJECT
public:
    CSwitchButton(QWidget *parent=0);
    void setChecked(bool state);
protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
private:
    void drawPressBackground(QPainter *painter);
    void drawPressSlide(QPainter *painter);
private:
    QColor m_offbkcolor1;
    QColor m_offbkcolor2;
    QColor m_onbkcolor1;
    QColor m_onbkcolor2;
    QColor m_slidecolor1;
    QColor m_slidecolor2;

    bool m_state;
    bool m_mouseDown;
    bool m_mouseMove;
    bool m_mouseUp;

    QPoint firstPoint;
    QPoint lastPoint;
signals:
    void checkStateChanged(bool currentState);
};

#endif // SWITCHCONTROL_H
