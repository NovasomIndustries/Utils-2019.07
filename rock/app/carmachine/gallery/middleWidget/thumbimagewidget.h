#ifndef THUMBIMAGEWIDGET_H
#define THUMBIMAGEWIDGET_H

#include "basewidget.h"

#include <QObject>
#include <QListWidget>
#include <QImage>
#include <QLabel>

#include "gallerymiddlewidgets.h"
#include "thumbimageitem.h"
#include "basepushbutton.h"

class galleryMiddleWidgets;

class thumbImageWidget:public baseWidget
{
    Q_OBJECT
public:
    thumbImageWidget(QWidget *parent);
private:
    void initLayout();
    void initConnection();
    void updateImageCount();
    void updateTipText();
private:
    galleryMiddleWidgets *m_middleWidgets;
    bool editMode;
    // control bottom
    QWidget *m_controlBottom;
    QLabel *m_imageCountText;
    QLabel *m_tipText;
    QPushButton *m_btnMode;
    QPushButton *m_btnUpdate;

    QListWidget *m_imageListWid;

    QMap<QString,QImage> m_imagesRes;
    QList<thumbImageItem*> m_selectedItems;

signals:
    void imagesResChanged(QMap<QString,QImage>);

private slots:
    void slot_onImagesResChanged(QMap<QString,QImage>);
    void slot_onListItemClick(QListWidgetItem*);
    void slot_changeImageMode();
    void slot_updateImages();

};


#endif // THUMBIMAGEWIDGET_H
