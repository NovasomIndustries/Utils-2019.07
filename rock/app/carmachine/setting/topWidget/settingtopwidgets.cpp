#include "settingtopwidgets.h"
#include <QLabel>
#include <QHBoxLayout>
#include "global_value.h"

settingTopWidgets::settingTopWidgets(QWidget *parent):baseWidget(parent)
{
    setObjectName("settingTopWidgets");
    setStyleSheet("#settingTopWidgets{background:rgb(56,58,66)}");
    initWidget();
}

void settingTopWidgets::initWidget()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed); // 竖排固定
    QHBoxLayout *hmainyout=new QHBoxLayout;

    m_btnreturn=new FourStateButton(return_resource_str,this);
    m_btnreturn->setFixedSize(return_icon_width,return_icon_height);

    m_btnicon=new flatButton(this);
    m_btnicon->setFixedSize(top_icon_size,top_icon_size);
    m_btnicon->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/music/music_top_icon.png)}");

    m_btnexit=new flatButton(this);
    m_btnmini=new flatButton(this);
    m_btnmobile=new flatButton(this);
    m_btnsetting=new flatButton(this);

    m_btnexit->setFixedSize(18,18);
    m_btnmini->setFixedSize(16,16);
    m_btnmobile->setFixedSize(16,16);
    m_btnsetting->setFixedSize(16,16);

    m_btnexit->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_close (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/main/btn_close (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/main/btn_close (3).png);}");
    m_btnmini->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_mini (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/main/btn_mini (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/main/btn_mini (3).png);}");
    m_btnmobile->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_mobile (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/main/btn_mobile (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/main/btn_mobile (3).png);}");
    m_btnsetting->setStyleSheet("QPushButton{border-image:url(:/image/main/btn_setting (1).png);}"
                                "QPushButton::hover{border-image:url(:/image/main/btn_setting (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/main/btn_setting (3).png);}");

    QLabel*label1=new QLabel("丨",this);
    label1->setFixedSize(6,16);
    label1->setStyleSheet("color:rgb(255,255,255,255);");
    label1->adjustSize();


    QLabel *titleText=new QLabel("Setting",this);
    QFont font = titleText->font();
    font.setPixelSize(font_size_big);
    titleText->setFont(font);
    titleText->setAlignment(Qt::AlignCenter);

    //layou1
    QHBoxLayout *lyout1 = new QHBoxLayout;
    lyout1->addWidget(m_btnreturn);
    lyout1->addSpacing(30);
    lyout1->addWidget(m_btnicon);
    lyout1->addStretch(0);

    //lyout2
    QHBoxLayout *lyout2 = new QHBoxLayout;
    lyout2->addWidget(label1);
    lyout2->addWidget(m_btnmobile);
    lyout2->addWidget(m_btnsetting);
    lyout2->addWidget(m_btnmini);
    lyout2->addWidget(m_btnexit);
    lyout2->addSpacing(10);
    lyout2->setSpacing(12);

    hmainyout->addLayout(lyout1);
    hmainyout->addWidget(titleText,1);
    hmainyout->addLayout(lyout2,1);
    hmainyout->setContentsMargins(0,0,0,0);
    setLayout(hmainyout);

    m_btnmobile->setVisible(false);
    m_btnsetting->setVisible(false);
    m_btnmini->setVisible(false);
    m_btnexit->setVisible(false);
}
