#include "gallerywidgets.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextCodec>
#include <QApplication>

#include "global_value.h"


galleryWidgets::galleryWidgets(QWidget *parent,mainWindow *mainWid):baseWidget(parent)
{
    setStyleSheet("QLabel{color:white;}");
    m_mainWid = mainWid ;
    initLayout();
    init();
}


void galleryWidgets::init()
{
    connect(m_topWid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_return()));
    connect(m_middleWid,SIGNAL(viewerResChanged(QString)),this,SLOT(slot_onViewerResChanged(QString)));
}

void galleryWidgets::initLayout()
{
    QVBoxLayout *vmainlyout = new QVBoxLayout;

    // the top widget of gallery page
    m_topWid = new galleryTopWidgets(this);
    // the middle widget of gallery page
    m_middleWid = new galleryMiddleWidgets(this);


    vmainlyout->addWidget(m_topWid);
    vmainlyout->addWidget(m_middleWid);
    vmainlyout->setContentsMargins(0,0,0,0);
    vmainlyout->setSpacing(0);

    setLayout(vmainlyout);
}

void galleryWidgets::slot_return()
{
    if(m_middleWid->isViewerMode()){
        m_middleWid->leaveViewerMode();
        m_topWid->updateTopTitle(str_top_title);
    }else{
        m_mainWid->slot_returnanimation();
    }
}

void galleryWidgets::slot_onViewerResChanged(QString imagePath)
{
    if(imagePath == "")
    {
        m_topWid->updateTopTitle(str_top_title);
    }
    else
    {
        QFileInfo *info = new QFileInfo(imagePath);
        if(info->exists())
        {
            m_topWid->updateTopTitle(info->fileName());
        }
    }
}

