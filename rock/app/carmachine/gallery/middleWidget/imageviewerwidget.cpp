#include "imageviewerwidget.h"

#include <QVBoxLayout>
#include <cmessagebox.h>
#include "global_value.h"


#ifdef DEVICE_EVB
int button_last_image_width = 100;
int layout_spacing = 50;

#else
int button_last_image_width = 40;
int layout_spacing = 30;

#endif

imageViewerWidget::imageViewerWidget(QWidget *parent):baseWidget(parent)
{
    setObjectName("imageViewerWidget");
    setStyleSheet("#imageViewerWidget{background:rgb(0,0,0)}");
    m_middleWidgets = (galleryMiddleWidgets*)parent;
    initLayout();
    initConnection();
}

void imageViewerWidget::initLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //    mainLayout->setStackingMode(QStackedLayout::StackAll);

    m_imageViewer = new ImageViewer(this);
    m_imageControler = new ImageControler(this);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(m_imageViewer);
    mainLayout->addWidget(m_imageControler);
    mainLayout->addSpacing(30);
    mainLayout->setMargin(0);

    setLayout(mainLayout);
}

void imageViewerWidget::initConnection()
{
    connect(this,SIGNAL(imagesResChanged(QMap<QString,QImage>,bool)),this,SLOT(slot_onImagesResChanged(QMap<QString,QImage>,bool)));

    connect(m_imageControler->m_btnLast,SIGNAL(clicked(bool)),this,SLOT(slot_lastImage()));
    connect(m_imageControler->m_btnNext,SIGNAL(clicked(bool)),this,SLOT(slot_nextImage()));
    connect(m_imageControler->m_btnZoomOut,SIGNAL(clicked(bool)),this,SLOT(slot_imageZoomOut()));
    connect(m_imageControler->m_btnZoomIn,SIGNAL(clicked(bool)),this,SLOT(slot_imageZoomIn()));
    connect(m_imageControler->m_btnRotate,SIGNAL(clicked(bool)),this,SLOT(slot_imageRotate()));
    connect(m_imageControler->m_btnDelete,SIGNAL(clicked(bool)),this,SLOT(slot_deleteImage()));
    connect(m_imageControler->m_btnDetail,SIGNAL(clicked(bool)),this,SLOT(slot_viewDetail()));
}

void imageViewerWidget::updateRes(QString imagePath, QImage image)
{
    m_imageViewer->setPixmap(QPixmap::fromImage(image));
    m_imagePath = imagePath;
    m_image = image;
    emit m_middleWidgets->viewerResChanged(imagePath);
}

void imageViewerWidget::slot_onImagesResChanged(QMap<QString,QImage> imagesRes,bool update)
{
    m_imagesRes = imagesRes;
    if(!m_imagesRes.keys().contains(m_imagePath)&&update)
    {
        QMap<QString,QImage>::Iterator  it = m_imagesRes.begin();
        updateRes(it.key(),it.value());
    }
}

void imageViewerWidget::slot_lastImage()
{
    QMap<QString,QImage>::Iterator  it = m_imagesRes.begin();
    while(it != m_imagesRes.end())
    {
        if(it.key() == m_imagePath)
        {
            if(it != m_imagesRes.begin()){
                --it;
            }else{
                it = m_imagesRes.end()-1;
            }
            updateRes(it.key(),it.value());
            break;
        }
        ++it;
    }
}

void imageViewerWidget::slot_nextImage()
{
    QMap<QString,QImage>::Iterator  it = m_imagesRes.begin();
    while(it!=m_imagesRes.end())
    {
        if(it.key() == m_imagePath)
        {
            if(it != (m_imagesRes.end()-1)){
                ++it;
            }else{
                it = m_imagesRes.begin();
            }
            updateRes(it.key(),it.value());
            break;
        }
        ++it;
    }
}

void imageViewerWidget::slot_viewDetail()
{
    QFileInfo *info = new QFileInfo(m_imagePath);
    if(info->exists())
    {
        ImageDetailWidget::showImageDetail(this,m_imagePath);
    }
}

void imageViewerWidget::slot_deleteImage()
{
    QFileInfo *info = new QFileInfo(m_imagePath);
    if(info->exists())
    {
        int result = CMessageBox::showCMessageBox(this,str_question_delete_image,str_button_delete,str_button_cancel);
        if(result == ChosseResult::RESULT_CONFIRM)
        {
            if(QFile::remove(m_imagePath)){
                QString removePath = m_imagePath;
                slot_nextImage();
                m_imagesRes.remove(removePath);
                m_middleWidgets->imagesResChanged(m_imagesRes);
            }
        }
    }
}

void imageViewerWidget::slot_imageZoomOut()
{
    m_imageViewer->zoomOut();
}

void imageViewerWidget::slot_imageZoomIn()
{
    m_imageViewer->zoomIn();
}

void imageViewerWidget::slot_imageRotate()
{
    m_imageViewer->clockwise90();
}
