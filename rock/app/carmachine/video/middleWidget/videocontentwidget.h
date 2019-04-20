#ifndef VIDEOCONTENTWIDGET_H
#define VIDEOCONTENTWIDGET_H

#include <QObject>
#include <QVideoWidget>
#include <QTimer>

class videoContentWidget: public QVideoWidget
{
    Q_OBJECT
public:
    videoContentWidget(QWidget *parent = 0);
private:
    void init();

    QTimer *m_timer;   // 定时器，区分单击和双击
protected:

    void mousePressEvent(QMouseEvent *event);  // 区分单击和双击事件的响应，单击播放暂停的切换，双击则是全屏
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void contentOneClick();
    void contentDoubleClick();
private slots:
    void onOneClick();
};

#endif // VIDEOCONTENTWIDGET_H
