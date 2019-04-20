#include "thumbimageitem.h"

thumbImageItem::thumbImageItem(QString imagePath,QImage image):QWidget()
  ,isChecked(false),toUpdate(false)
{
    m_imagePath = imagePath;
    m_image = image;
    initLayout();

    imageMapper = new brightnessMapper;
}

void thumbImageItem::initLayout()
{
    m_stackedLayout = new QStackedLayout();

    // image widget
    thumbImage = new QLabel(this);

    // checkbox layout
    QVBoxLayout *m_statusLayout = new QVBoxLayout;

    m_checkImage = new QLabel(this);
    m_checkImage->setPixmap(QPixmap(":/image/gallery/ic_thumb_checked.png").scaled(40,40));

    m_statusLayout->addStretch(0);
    m_statusLayout->addWidget(m_checkImage);

    QWidget *m_statusWid = new QWidget(this);
    m_statusWid->setLayout(m_statusLayout);


    m_stackedLayout->setStackingMode(QStackedLayout::StackAll);
    m_stackedLayout->addWidget(thumbImage);
    m_stackedLayout->addWidget(m_statusWid);
    m_stackedLayout->setCurrentIndex(0);

    setLayout(m_stackedLayout);
}

void thumbImageItem::resizeEvent(QResizeEvent *)
{
    thumbImage->setPixmap(QPixmap::fromImage(m_image).scaled(width(),height()));
}


void thumbImageItem::paintEvent(QPaintEvent *)
{
    if(toUpdate)
    {
        if(isChecked)
        {
            imageMapper->updateBCG(0.5,1,1);
            thumbImage->setPixmap(QPixmap::fromImage(imageMapper->apply(m_image)).scaled(width(),height()));
        }
        else
        {
             thumbImage->setPixmap(QPixmap::fromImage(m_image).scaled(width(),height()));
        }
        toUpdate = false;
    }
}


void thumbImageItem::onItemClick()
{
    if(isChecked)
    {
        m_stackedLayout->setCurrentIndex(0);
        isChecked = false;
    }
    else
    {
        m_stackedLayout->setCurrentIndex(1);
        isChecked = true;
    }
    toUpdate = true;
    update();
}

