#include "emptyimageswidget.h"
#include "QVBoxLayout"

#include <QLabel>
#include "basepushbutton.h"
#include "global_value.h"

#ifdef DEVICE_EVB
int center_image_width = 300;
#else
int center_image_width = 150;
#endif

emptyImagesWidget::emptyImagesWidget(QWidget *parent):baseWidget(parent)
{
    setStyleSheet("QLabel{color:white}");
    initLayout();
}
void emptyImagesWidget::initLayout()
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    flatButton *centerImage = new flatButton(this);
    centerImage->setEnabled(false);
    centerImage->setFixedSize(center_image_width,center_image_width);
    centerImage->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/gallery/ic_empty_image.png)}");

    QHBoxLayout *centerImageLyout = new QHBoxLayout;
    centerImageLyout->addStretch(0);
    centerImageLyout->addWidget(centerImage);
    centerImageLyout->addStretch(0);

    QLabel *tip1 = new QLabel(str_gallery_empty_tip1,this);
    tip1->setAlignment(Qt::AlignCenter);

    QLabel *tip2 = new QLabel(str_gallery_empty_tip2,this);
    tip2->setAlignment(Qt::AlignCenter);

    vmainlyout->addStretch(0);
    vmainlyout->addLayout(centerImageLyout);
    vmainlyout->addWidget(tip1);
    vmainlyout->addWidget(tip2);
    vmainlyout->addSpacing(100);
    vmainlyout->addStretch(0);
    vmainlyout->setSpacing(15);

    // in order to set the layout in the center of page
    QHBoxLayout *lyout = new QHBoxLayout;
    lyout->addStretch(1);
    lyout->addLayout(vmainlyout);
    lyout->addStretch(1);

    setLayout(lyout);
}
