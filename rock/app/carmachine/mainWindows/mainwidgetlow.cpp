#include "mainwidgetlow.h"
#include <QHBoxLayout>
#include <global_value.h>

#ifdef DEVICE_EVB
int tab_icon_size = 150;
#else
int tab_icon_size = 80;
#endif

mainWidgetLow::mainWidgetLow(QWidget *parent):baseWidget(parent)
{
    initLayout();
}

void mainWidgetLow::initLayout()
{
#ifndef DEVICE_EVB
    m_btnEasyConnect = new guideButton(":/image/main/icon_easy_connect.png","easyConnect",this);
    m_btnEasyConnect->setFixedSize(tab_icon_size,tab_icon_size);

    m_btnCarplay = new guideButton(":/image/main/icon_carplay.png","carplay",this);
    m_btnCarplay->setFixedSize(tab_icon_size,tab_icon_size);
#endif

    m_btnSetUp = new guideButton(":/image/main/icon_setting.png","radio",this);
    m_btnMusic = new guideButton(":/image/main/icon_music.png","music",this);
    m_btnVideo = new guideButton(":/image/main/icon_video.png","video",this);
    m_btnGallery = new guideButton(":/image/main/icon_gallery.png","video",this);
    m_btnCamera = new guideButton(":/image/main/icon_guide.png","camera",this);

    m_btnSetUp->setFixedSize(tab_icon_size,tab_icon_size);
    m_btnMusic->setFixedSize(tab_icon_size,tab_icon_size);
    m_btnVideo->setFixedSize(tab_icon_size,tab_icon_size);
    m_btnGallery->setFixedSize(tab_icon_size,tab_icon_size);
    m_btnCamera->setFixedSize(tab_icon_size,tab_icon_size);

    QHBoxLayout *hmianlyout = new QHBoxLayout;
    hmianlyout->addStretch(2);
#ifndef DEVICE_EVB
    hmianlyout->addWidget(m_btnEasyConnect,1);
    hmianlyout->addWidget(m_btnCarplay,1);
#endif
    hmianlyout->addWidget(m_btnSetUp,1);
    hmianlyout->addWidget(m_btnMusic,1);
    hmianlyout->addWidget(m_btnVideo,1);
    hmianlyout->addWidget(m_btnGallery,1);
    hmianlyout->addWidget(m_btnCamera,1);
    hmianlyout->addStretch(1);
    hmianlyout->setContentsMargins(50,0,25,0);
    hmianlyout->setSpacing(40);

    setLayout(hmianlyout);
}
