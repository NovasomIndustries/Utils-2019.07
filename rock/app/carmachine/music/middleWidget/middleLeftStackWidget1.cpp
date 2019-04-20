#include "middleLeftStackWidget1.h"
#include "QLabel"
#include "basepushbutton.h"
#include <QVBoxLayout>
#include <QPainter>

middleLeftStackWidget1::middleLeftStackWidget1(QWidget*parent):baseWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    initLayout();
}

void middleLeftStackWidget1::initLayout()
{
    QVBoxLayout *vLyout=new QVBoxLayout;
    QLabel *label=new QLabel(this);
    label->setPixmap(QPixmap(":/image/music/lab_backups.png"));
    label->setFixedSize(146,90);

    QLabel *label2=new QLabel("Cloud Backup Multi-screen Display",this);
    label2->adjustSize();
    label2->setAlignment(Qt::AlignHCenter);
    label2->setStyleSheet("color:rgb(52,52,52)");


//    QLabel *label3=new QLabel("Your list has 0 songs that are not backed up",this);
//    label3->adjustSize();
//    label3->setAlignment(Qt::AlignHCenter);
//    label3->setStyleSheet("color:rgb(51,51,51);");

    flatButton *btn=new flatButton("Use this",this);
    btn->setFixedSize(170,36);
    btn->setStyleSheet("QPushButton{color:rgb(80,80,80);border: 1px solid rgb(229,229,229);background:rgb(240,240,240);}"
                       "QPushButton:hover{color:rgb(30,30,30);border: 1px solid rgb(219,219,219);background:rgb(229,229,229);}"
                       "QPushButton:pressed{color:rgb(80,80,80);border: 1px solid rgb(229,229,229);background:rgb(240,240,240);}");


    vLyout->addSpacerItem(new QSpacerItem(10,40,QSizePolicy::Expanding,QSizePolicy::Expanding));
    vLyout->addWidget(label,0,Qt::AlignHCenter);
    vLyout->addSpacing(25);
    vLyout->addWidget(label2,0,Qt::AlignHCenter);
//    vLyout->addWidget(label3,0,Qt::AlignHCenter);
    vLyout->addSpacing(20);
    vLyout->addWidget(btn,0,Qt::AlignHCenter);
    vLyout->addSpacing(100);
    vLyout->addSpacerItem(new QSpacerItem(10,50,QSizePolicy::Expanding,QSizePolicy::Expanding));

    vLyout->setContentsMargins(0,0,0,0);
    this->setLayout(vLyout);
}
