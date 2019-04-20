#include "gallerymiddlewidgets.h"
#include <QDir>
#include <qdebug.h>
#include <QApplication>
#include <QDirIterator>
#include <QDateTime>

#include "global_value.h"

galleryMiddleWidgets::galleryMiddleWidgets(QWidget *parent):baseWidget(parent)
{
    setObjectName("galleryMiddleWidgets");
    setStyleSheet("#galleryMiddleWidgets{background:rgb(43,45,51)}");
    initLayout();
    initConnection();
}

/**
 * @brief used to find all image file in path
 * @param path
 * @return
 */
QFileInfoList findImgFiles(const QString& path)
{
    QFileInfoList imageFiles;

    QDirIterator it(path,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    while (it.hasNext())
    {
        QString name = it.next();
        QFileInfo info(name);
        if (info.isDir())
        {
            imageFiles.append(findImgFiles(name));
        }
        else
        {
            if (info.suffix().compare("jpg",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("bmp",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("png",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("bmp",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("jpeg",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("titf",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("svg",Qt::CaseInsensitive) == 0
                    ||info.suffix().compare("gif",Qt::CaseInsensitive) == 0)
            {
                imageFiles.append(info);
            }
        }
    }
    return imageFiles;
}


/**
 * @brief used to find all image Res in path
 * @param path
 * @return
 */
QMap<QString,QImage> galleryMiddleWidgets::getImageResFromPath(const QString& path)
{
    QFileInfoList imageFiles = findImgFiles(path);
    QMap<QString,QImage> imageRes;

    QImage tempImage;
    for(int i = 0;i < imageFiles.size();i++)
    {
        if(tempImage.load(imageFiles.at(i).absoluteFilePath()))
        {
            imageRes.insert(imageFiles.at(i).absoluteFilePath(),tempImage);
        }
    }
    return imageRes;
}


void galleryMiddleWidgets::updateResUi(QMap<QString,QImage> imageRes)
{
    m_imagesInfoList.clear();
    m_imagesRes.clear();

    m_imagesRes = imageRes;
    slot_onImagesResChanged(m_imagesRes);
}

void galleryMiddleWidgets::initConnection()
{
    connect(this,SIGNAL(imageEmpty()),this,SLOT(slot_showEmptyImageTip()));
    connect(this,SIGNAL(imageItemClick(QString,QImage)),this,SLOT(slot_showImageViewer(QString,QImage)));
    connect(this,SIGNAL(imagesResChanged(QMap<QString,QImage>)),this,SLOT(slot_onImagesResChanged(QMap<QString,QImage>)));
}

void galleryMiddleWidgets::initLayout()
{
    m_stackedMainLyout = new QStackedLayout(this);

    m_emptyImgWid = new emptyImagesWidget(this);
    m_thumbImgWid = new thumbImageWidget(this);
    m_viewerWid = new imageViewerWidget(this);

    m_stackedMainLyout->addWidget(m_emptyImgWid);
    m_stackedMainLyout->addWidget(m_thumbImgWid);
    m_stackedMainLyout->addWidget(m_viewerWid);
    m_stackedMainLyout->setCurrentWidget(m_thumbImgWid);

    setLayout(m_stackedMainLyout);
}

void galleryMiddleWidgets::slot_showEmptyImageTip()
{
    emit viewerResChanged("");
    m_stackedMainLyout->setCurrentWidget(m_emptyImgWid);
}

void galleryMiddleWidgets::slot_showImageViewer(QString imagePath, QImage image)
{
    m_stackedMainLyout->setCurrentWidget(m_viewerWid);
    m_viewerWid->updateRes(imagePath,image);
}

void galleryMiddleWidgets::slot_onImagesResChanged(QMap<QString, QImage> imagesRes)
{
    m_imagesRes = imagesRes;
    if(m_imagesRes.size()>0)
    {
        if(m_stackedMainLyout->currentWidget()==m_emptyImgWid)
        {
            m_stackedMainLyout->setCurrentWidget(m_thumbImgWid);
        }
        emit m_thumbImgWid->imagesResChanged(m_imagesRes);
        emit m_viewerWid->imagesResChanged(m_imagesRes,m_stackedMainLyout->currentWidget()==m_viewerWid);
    }
    else
    {
        emit imageEmpty();
    }
}

void galleryMiddleWidgets::leaveViewerMode()
{
    m_stackedMainLyout->setCurrentWidget(m_thumbImgWid);
}



