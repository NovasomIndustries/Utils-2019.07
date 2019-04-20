#include "thumbimagewidget.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QCheckBox>

#include "thumbimageitem.h"
#include "global_value.h"
#include <cmessagebox.h>

#ifdef DEVICE_EVB
int thumb_image_width = 280;
int bottom_widget_height = 130;
int button_width = 130;
int button_height = 60;

#else
int thumb_image_width = 110;
int bottom_widget_height = 50;
int button_width = 60;
int button_height = 30;

#endif

thumbImageWidget::thumbImageWidget(QWidget *parent):baseWidget(parent),editMode(false)
{
    m_middleWidgets = (galleryMiddleWidgets*)parent;
    initLayout();
    initConnection();
}

void thumbImageWidget::initLayout()
{
    QVBoxLayout *mainLyout = new QVBoxLayout;

    // control bottom
    m_controlBottom = new QWidget(this);
    m_controlBottom->setStyleSheet("background:rgb(20,22,28)");
    m_controlBottom->setFixedHeight(bottom_widget_height);

    m_imageCountText = new QLabel(this);
    m_imageCountText->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QFont font = m_imageCountText->font();
    font.setPixelSize(font_size_big);
    m_imageCountText->setFont(font);
    m_imageCountText->adjustSize();

    m_tipText = new QLabel(this);
    m_tipText->setFont(font);
    m_tipText->adjustSize();

    m_btnMode = new QPushButton(str_button_edit_image,this);
    m_btnMode->setStyleSheet("QPushButton{background:rgb(36,184,71);color:white;border-radius:5px}"
                             "QPushButton::hover{background:rgb(25,166,58)}"
                             "QPushButton::pressed{background:rgb(25,166,58)}");
    m_btnUpdate = new QPushButton(str_button_refresh_image,this);
    m_btnUpdate->setStyleSheet("QPushButton{background:rgb(36,184,71);color:white;border-radius:5px}"
                               "QPushButton::hover{background:rgb(25,166,58)}"
                               "QPushButton::pressed{background:rgb(25,166,58)}");

    m_btnMode->setFixedSize(button_width,button_height);
    m_btnUpdate->setFixedSize(button_width,button_height);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacing(0);
    buttonLayout->addWidget(m_btnUpdate);
    buttonLayout->addWidget(m_btnMode);
    buttonLayout->setSpacing(20);
    buttonLayout->addSpacing(20);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_imageCountText,1);
    bottomLayout->addWidget(m_tipText,1);
    bottomLayout->addLayout(buttonLayout,1);

    m_controlBottom->setLayout(bottomLayout);

    // listWidget
    m_imageListWid = new QListWidget(this);
    m_imageListWid->setIconSize(QSize(thumb_image_width,thumb_image_width));
    m_imageListWid->setStyleSheet("QListWidget::item:selected{background: transparent;}");
    /* cancel the border in ListWidget */
    m_imageListWid->setFrameShape(QListWidget::NoFrame);
    /* set QListWidget be IconMode to show image thumnail and unable to drag */
    m_imageListWid->setViewMode(QListView::IconMode);
    m_imageListWid->setMovement(QListView::Static);
    m_imageListWid->setSpacing(10);
    m_imageListWid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_imageListWid->setFocusPolicy(Qt::NoFocus);
    m_imageListWid->setStyleSheet("QListWidget::indicator{subcontrol-position:top;}"
                                  "QListWidget{background:transparent}");


    mainLyout->addWidget(m_imageListWid);
    mainLyout->addWidget(m_controlBottom);
    mainLyout->setContentsMargins(0,0,0,0);
    mainLyout->setSpacing(0);

    setLayout(mainLyout);
}

void thumbImageWidget::initConnection()
{
    connect(this,SIGNAL(imagesResChanged(QMap<QString,QImage>)),this,SLOT(slot_onImagesResChanged(QMap<QString,QImage>)));
    connect(m_btnMode,SIGNAL(clicked(bool)),this,SLOT(slot_changeImageMode()));
    connect(m_btnUpdate,SIGNAL(clicked(bool)),this,SLOT(slot_updateImages()));
    connect(m_imageListWid,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slot_onListItemClick(QListWidgetItem*)));

}

void thumbImageWidget::updateImageCount()
{
    m_imageCountText->setText(str_image_and_preview+"("+QString::number(m_imageListWid->count())+")");
}

void thumbImageWidget::updateTipText()
{
    if(!editMode){
        m_tipText->setText("");
    }else{
        m_tipText->setText(str_imge_have_seleted1+QString::number(m_selectedItems.size())+str_imge_have_seleted2);
    }
}

void thumbImageWidget::slot_onImagesResChanged(QMap<QString,QImage> imagesRes)
{
    m_imagesRes.clear();
    m_imageListWid->clear();
    if(editMode)
    {
        slot_changeImageMode();
    }
    m_imagesRes = imagesRes;

    QMap<QString,QImage>::Iterator  it = imagesRes.begin();
    while(it!=imagesRes.end())
    {
        QListWidgetItem *litsItem = new QListWidgetItem(/*QIcon(QPixmap::fromImage(m_images.at(i)).scaled(130,130)),NULL*/);

        thumbImageItem *itemWid = new thumbImageItem(it.key(),it.value());

        litsItem->setSizeHint(QSize(thumb_image_width,thumb_image_width));
        m_imageListWid ->addItem(litsItem);
        m_imageListWid->setItemWidget(litsItem,itemWid);
        ++it;
    }
    updateImageCount();
    if(m_imageListWid->count()==0)
    {
        emit m_middleWidgets->imageEmpty();
    }
}

void thumbImageWidget::slot_onListItemClick(QListWidgetItem *listItem)
{
    thumbImageItem *imageItem = (thumbImageItem*)m_imageListWid->itemWidget(listItem);
    if(editMode)
    {
        imageItem->onItemClick();

        if(imageItem->getCheckState()){
            m_selectedItems.append(imageItem);
        }else{
            m_selectedItems.removeOne(imageItem);
        }
        updateTipText();
    }
    else
    {
        emit m_middleWidgets->imageItemClick(imageItem->getImagePath(),imageItem->getImage());
    }
}

void thumbImageWidget::slot_changeImageMode()
{
    if(editMode)
    {
        for(int i=0;i<m_selectedItems.size();i++)
        {
            m_selectedItems.at(i)->onItemClick();
        }
        m_selectedItems.clear();
        editMode = false;
        m_btnUpdate->setText(str_button_refresh_image);
        m_btnMode->setText(str_button_edit_image);
        updateTipText();
    }
    else
    {
        editMode = true;
        m_btnUpdate->setText(str_button_delete_image);
        m_btnMode->setText(str_button_edit_image_cancel);
        updateTipText();
    }
}

void thumbImageWidget::slot_updateImages()
{
    if(m_selectedItems.size()>0&&editMode){
        int result = CMessageBox::showCMessageBox(this,str_question_delete_image,str_button_delete,str_button_cancel);
        if(result == RESULT_CONFIRM)
        {
            // delete images selected
            for(int i=0;i<m_selectedItems.size();i++)
            {
                thumbImageItem *imageItem = m_selectedItems.at(i);
                if(QFile::remove(imageItem->getImagePath())){
                    m_imagesRes.remove(imageItem->getImagePath());
                }
            }
            emit m_middleWidgets->imagesResChanged(m_imagesRes);
        }
    }else{   // reserch images
        mainwid->slot_updateMedia2();
    }
}
