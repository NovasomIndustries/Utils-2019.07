#ifndef GALLERYMIDDLEWIDGETS_H
#define GALLERYMIDDLEWIDGETS_H

#include "basewidget.h"
#include "emptyimageswidget.h"
#include "thumbimagewidget.h"
#include "imageviewerwidget.h"

#include <QStackedLayout>
#include <QListWidget>
#include <QFileInfoList>


class thumbImageWidget;
class imageViewerWidget;

class galleryMiddleWidgets:public baseWidget
{
    Q_OBJECT
public:
    galleryMiddleWidgets(QWidget *parent);
    QMap<QString,QImage> getImageResFromPath(const QString& path = QString(""));
    void updateResUi(QMap<QString,QImage> imageRes);
    bool isViewerMode(){return m_stackedMainLyout->currentWidget() == (QWidget*)m_viewerWid;}
    void leaveViewerMode();
private:
    galleryMiddleWidgets *m_middleWidgets;
    QFileInfoList m_imagesInfoList;

    QMap<QString,QImage> m_imagesRes;

    QStackedLayout *m_stackedMainLyout;  // the middle page's main layout
    emptyImagesWidget *m_emptyImgWid;
    thumbImageWidget *m_thumbImgWid;
    imageViewerWidget *m_viewerWid;

private:
    void initLayout();
    void initConnection();

signals:
    void imagesResChanged(QMap<QString,QImage>);
    void imageEmpty();
    void imageItemClick(QString imagePath,QImage image);
    void viewerResChanged(QString filePath);
private slots:
    void slot_showEmptyImageTip();
    void slot_showImageViewer(QString imagePath,QImage image);
    void slot_onImagesResChanged(QMap<QString,QImage>);
};

#endif // GALLERYMIDDLEWIDGETS_H
