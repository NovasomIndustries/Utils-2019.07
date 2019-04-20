#include "videobottomwidgets.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#ifdef DEVICE_EVB
int video_bottom_height  = 160;
int video_playButton_size = 100;
int openFile_size = 80;
#else
int video_bottom_height  = 70;
int video_playButton_size = 50;
int openFile_size = 30;
#endif

videoBottomWidgets::videoBottomWidgets(QWidget *parent):baseWidget(parent)
{
    setObjectName("videoBottomWidgets");
    setStyleSheet("#videoBottomWidgets{background:rgb(89,92,102)}");
    setFixedHeight(video_bottom_height);
    initLayout();
}

void videoBottomWidgets::initLayout()
{
    QHBoxLayout *hmainlyout = new QHBoxLayout;

    m_btnPlayPause = new flatButton(this);
    m_btnNext = new flatButton(this);
    m_btnLast = new flatButton(this);
    m_btnOpenFile = new flatButton(this);
    m_volWidget = new volWidget(this);

    m_btnPlayPause->setFixedSize(video_playButton_size,video_playButton_size);
    m_btnNext->setFixedSize(video_playButton_size,video_playButton_size);
    m_btnLast->setFixedSize(video_playButton_size,video_playButton_size);
    m_btnOpenFile->setFixedSize(video_playButton_size,video_playButton_size);

    m_btnNext->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_next (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_next (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_next (3).png);}");
    m_btnLast->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_previous (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_previous (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_previous (3).png);}");
    m_btnPlayPause->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_play (1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/music/btn_play (2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/music/btn_play (3).png);}");

    m_btnOpenFile->setStyleSheet("QPushButton{border-image:url(:/image/video/video_open_file.png);}");
#ifdef DEVICE_EVB
    m_btnOpenFile->setVisible(false);
#endif

    // first layout
    QHBoxLayout *hlyout1 = new QHBoxLayout;
    hlyout1->addSpacing(80);
    hlyout1->addWidget(m_btnOpenFile);
    hlyout1->addSpacing(40);
    hlyout1->addWidget(m_volWidget);
    hlyout1->addStretch(0);

    // second layout
    QHBoxLayout *hlyout2 = new QHBoxLayout;
    hlyout2->addWidget(m_btnLast);
    hlyout2->addSpacing(20);
    hlyout2->addWidget(m_btnPlayPause);
    hlyout2->addSpacing(20);
    hlyout2->addWidget(m_btnNext);

    hmainlyout->addLayout(hlyout1,1);
    hmainlyout->addLayout(hlyout2,1);
    hmainlyout->addStretch(1);
    hmainlyout->setContentsMargins(0,0,0,0);

    setLayout(hmainlyout);}

void videoBottomWidgets::setPlayingStyle()
{
    m_btnPlayPause->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_pause (1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/music/btn_pause (2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/music/btn_pause (3).png);}");

}

void videoBottomWidgets::setPauseStyle()
{
    m_btnPlayPause->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_play (1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/music/btn_play (2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/music/btn_play (3).png);}");
}
