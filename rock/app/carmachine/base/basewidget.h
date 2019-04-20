#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QObject>
#include <QWidget>

// 1. 包含鼠标点击的通用事件
// 2. 解决setStyleSheet与信号与槽机制的冲突
class baseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit baseWidget(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *);   // 重写paintEvent事件，即能setStyleSheet,也能使用信号与槽
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
signals:

public slots:
};

#endif // BASEWIDGET_H
