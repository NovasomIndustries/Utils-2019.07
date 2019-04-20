#include "basewidget.h"
#include <QStyleOption>
#include <QPainter>

#include "mainwindow.h"

baseWidget::baseWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

// 解决信号和槽机制与setStyleSheet的冲突
void baseWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void baseWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void baseWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
}

void baseWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
}

void baseWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

}
void baseWidget::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
}

void baseWidget::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
}

void baseWidget::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
}
