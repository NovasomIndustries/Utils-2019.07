#ifndef PLAYMODEWIDGET_H
#define PLAYMODEWIDGET_H
#include "basewidget.h"
#include <QPushButton>
#include "player/medialist.h"

class playModeButton:public QPushButton
{
    Q_OBJECT
public:
    explicit playModeButton(QString pixnormal,QString pixhover,QString text,QWidget*parent);
    void setCheckedBtn(bool check);
    void setPlayMode(PlayMode mode){m_mode=mode;}
    PlayMode& playMode(){return m_mode;}
protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void paintEvent(QPaintEvent *);
private:
    bool m_enter;
    bool m_pressed;
    PlayMode m_mode;
    QPixmap m_pixnormal;
    QPixmap m_pixhover;
    QString m_text;
};

class playModeWidget:public baseWidget
{
    Q_OBJECT
public:
    explicit playModeWidget(QWidget*parent=0);
    void init();
    void setCurrentMode(PlayMode);

    QVector<playModeButton*> m_vector;
    playModeButton *m_btnOrder;
    playModeButton *m_btnRandom;
    playModeButton *m_btnOneCircle;
private slots:
    void slot_setCurrentMode();
signals:
    void sig_CurrentModeChange(PlayMode);
protected:
    void mousePressEvent(QMouseEvent *){}
    void mouseMoveEvent(QMouseEvent *){}
    void focusOutEvent(QFocusEvent*){this->hide();}
private:

};


#endif // PLAYMODEWIDGET_H
