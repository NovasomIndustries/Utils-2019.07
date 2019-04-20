#ifndef IMAGEVIEWERWIDGET_H
#define IMAGEVIEWERWIDGET_H

#include "basewidget.h"
#include "basepushbutton.h"
#include "gallerymiddlewidgets.h"
#include "imagedetailwidget.h"
#include "imageviewer.h"
#include "imagecontroler.h"

#include <QLabel>

class galleryMiddleWidgets;

class imageViewerWidget:public baseWidget
{
    Q_OBJECT
public:
    imageViewerWidget(QWidget *parent = 0);

    void updateRes(QString imagePath,QImage image);
private:
    void initLayout();
    void initConnection();
private:
    galleryMiddleWidgets *m_middleWidgets;

    QMap<QString,QImage> m_imagesRes;
    QString m_imagePath;
    QImage m_image;

    // imageViewer: 对图片进行显示与操作
    ImageViewer *m_imageViewer;
    ImageControler *m_imageControler;

protected:

private slots:
    void slot_onImagesResChanged(QMap<QString,QImage>,bool);
    void slot_lastImage();
    void slot_nextImage();
    void slot_viewDetail();
    void slot_deleteImage();
    void slot_imageZoomOut();
    void slot_imageZoomIn();
    void slot_imageRotate();
signals:
    void imagesResChanged(QMap<QString,QImage>,bool);
};

#endif // IMAGEVIEWERWIDGET_H
