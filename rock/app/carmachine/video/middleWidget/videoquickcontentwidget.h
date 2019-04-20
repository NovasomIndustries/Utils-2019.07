#ifndef VIDEOQUICKCONTENTWIDGET_H
#define VIDEOQUICKCONTENTWIDGET_H
#include <QQuickWidget>
#include <QObject>
#include <QTimer>


class videoQuickContentWidget:public QQuickWidget
{
    Q_OBJECT
public:
    videoQuickContentWidget(QWidget *parent = 0);

    void setFullScreen(bool fullScreen);
private:
    int normalWidth;
    int normalHeight;
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

#endif // VIDEOQUICKCONTENTWIDGET_H
