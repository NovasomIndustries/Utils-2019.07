#ifndef IMAGEBROWSER_IMAGEHANDLER_H
#define IMAGEBROWSER_IMAGEHANDLER_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QGestureEvent>
#include <QPinchGesture>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);
    void setPixmap(const QPixmap &pixmap);

    void showOriginalSize();
    void showSuitableSize();
    void zoomIn();
    void zoomOut();
    void clockwise90();
    void anticlockwise90();

private:
    void ariseScale(int rate);

signals:
    void percentageChanged(double percentage);
    void rightButtonClicked();

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool event(QEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QPixmap m_pixmap;

    //缩放
    double m_scale;             //缩放比例
    double m_percentage;          //缩放百分比

    //移动
    QPoint m_pressPoint;                //鼠标按下点的坐标
    double m_originX;
    double m_originY;
    double m_basicX;
    double m_basicY;

    int m_suitableWidth;
    int m_suitableHeight;

    qreal currentStepScaleFactor;
};
#endif // IMAGEBROWSER_IMAGEHANDLER_H
