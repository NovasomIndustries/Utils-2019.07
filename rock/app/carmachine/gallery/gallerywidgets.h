#ifndef GALLERYWIDGETS_H
#define GALLERYWIDGETS_H

#include "basewidget.h"
#include "gallerytopwidgets.h"
#include "middleWidget/gallerymiddlewidgets.h"
#include "mainwindow.h"

#include <QObject>

class mainWindow;

class galleryWidgets:public baseWidget
{
    Q_OBJECT
public:
    galleryWidgets(QWidget *parent,mainWindow *mainWid);
    mainWindow *m_mainWid;

    galleryTopWidgets *m_topWid;
    galleryMiddleWidgets *m_middleWid;
private:
    void init();
    void initLayout();

private slots:
    void slot_return();
    void slot_onViewerResChanged(QString);
};

#endif // GALLERYWIDGETS_H
