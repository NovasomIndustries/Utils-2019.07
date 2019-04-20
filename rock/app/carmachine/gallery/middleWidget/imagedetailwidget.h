#ifndef IMAGEDETAILWIDGET_H
#define IMAGEDETAILWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QEventLoop>

#include "basepushbutton.h"

class ImageItem:public QWidget
{
public:
    ImageItem(QWidget *parent=0);
    void updateItem(QString title,QString text);
private:
    QLabel *titleLabel;
    QLabel *textLabel;
};

class ImageDetailWidget:public QDialog
{
    Q_OBJECT
public:
    ImageDetailWidget(QWidget *parent=0);

    int static showImageDetail(QWidget *parent,QString imagePath);
private:
    void initLayout();
    void initConnection();
protected:
    int exec();
    void closeEvent(QCloseEvent *event);
public:
    flatButton *m_btnConfirm;

    ImageItem *nameItem;
    ImageItem *patternItem;
    ImageItem *resolutionItem;
    ImageItem *locationItem;
    ImageItem *sizeItem;
    ImageItem *createTimeItem;

    QEventLoop* m_eventLoop;


};

#endif // IMAGEDETAILWIDGET_H
