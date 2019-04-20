#include "videomiddlewidgetright.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDir>
#include <QTime>
#include <QFileDialog>
#include <QEventLoop>
#include <QMediaPlayer>
#include <QDirIterator>

#include "player/videomediadatabase.h"
#include "global_value.h"

videoMiddleWidgetRight::videoMiddleWidgetRight(QWidget *parent):baseWidget(parent)
{
    setObjectName("videoMiddleWidgetRight");
    setStyleSheet("#videoMiddleWidgetRight{background:rgb(43,45,51)}");

    m_playList = new videoList(this);
    m_curPlayingIndex = -1;
    initLayout();
    initConnection();
}

void videoMiddleWidgetRight::initLayout()
{
    QVBoxLayout *vmianlyout = new QVBoxLayout;

    m_listHeader = new listHeader(this);
    m_listHeader->setVisible(false);
    m_listHeader->setFixedHeight(100);

    m_stackedWid = new QStackedWidget(this);
    m_localTable = new videoLocalListTable(m_stackedWid);
    m_netTable = new videoNetListTable(m_stackedWid);

    m_stackedWid->addWidget(m_localTable);
    m_stackedWid->addWidget(m_netTable);

    vmianlyout->addWidget(m_listHeader);
    vmianlyout->addWidget(m_stackedWid);
    vmianlyout->setContentsMargins(40,0,40,0);

    setLayout(vmianlyout);
}

void videoMiddleWidgetRight::initConnection()
{
    connect(m_listHeader,SIGNAL(buttonLocalClick()),this,SLOT(slot_switchToLocalList()));
    connect(m_listHeader,SIGNAL(buttonNetClick()),this,SLOT(slot_switchToNetList()));

    //    connect(m_localTable,SIGNAL(cellDoubleClicked(int,int)),this,SIGNAL(sig_localTableItemDoubleClick(int,int)));
}

void videoMiddleWidgetRight::setOriginState()
{
    if(m_curPlayingIndex!=-1)
    {
        m_localTable->setRowTextColor(m_curPlayingIndex,QColor(255,255,255));
        m_localTable->item(m_curPlayingIndex,1)->setText("");
        m_curPlayingIndex = -1;
        m_localTable->setCurrentCell(-1,0);
    }
}


/**
 * @brief used to find all video file in path
 * @param path
 * @return
 */
QFileInfoList videoMiddleWidgetRight::findVideoFiles(const QString& path)
{
    QFileInfoList videoFiles;

    QDirIterator it(path,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    while (it.hasNext())
    {
        QString name = it.next();
        QFileInfo info(name);
        if (info.isDir())
        {
            videoFiles.append(findVideoFiles(name));
        }
        else
        {
            if (info.suffix() == "mp4" || info.suffix() == "avi" || info.suffix() == "rm"
                    ||info.suffix() == "rmvb" || info.suffix() == "wmv" || info.suffix() == "mkv"
                    ||info.suffix() == "mov" || info.suffix() == "asf" || info.suffix() == "ts")
            {
                videoFiles.append(info);
            }
        }
    }
    return videoFiles;
}


void videoMiddleWidgetRight::updateResUi(QFileInfoList fileList)
{
    // clear list
    for(int i = m_localTable->rowCount();i > 0;i--)
    {
        m_localTable->removeRow(0);
    }
    m_playList->clearList();

    for(int i=0;i<fileList.size();i++){
        QFileInfo fileInfo = fileList.at(i);
        if(!m_playList->getUrlList().contains(QUrl::fromLocalFile(fileInfo.absoluteFilePath()))){
            int rowCount = m_localTable->rowCount();
            insertIntoLocalTable(rowCount,fileInfo.fileName()," ");
            m_playList->addToPlayList(fileInfo.absoluteFilePath());
        }
    }
    m_curPlayingIndex = -1;
}


void videoMiddleWidgetRight::insertIntoLocalTable(int row, QString videoName, QString duration)
{
    m_localTable->insertRow(row);
    m_localTable->setItem(row,0,new QTableWidgetItem(videoName));
    m_localTable->setItem(row,1,new QTableWidgetItem(duration));
    m_localTable->item(row,1)->setTextAlignment(Qt::AlignVCenter|Qt::AlignRight);
}

void videoMiddleWidgetRight::updatePlayingItemStyle(QMediaContent content)
{
    QList<QUrl> urlList = m_playList->getUrlList();
    // 还原上次选中的item
    if(m_curPlayingIndex!=-1)
    {
        m_localTable->setRowTextColor(m_curPlayingIndex,QColor(255,255,255));
        m_localTable->item(m_curPlayingIndex,1)->setText(m_curPlayingDuration);
        m_curPlayingIndex = -1;
        m_localTable->setPlayingItemIndex(m_curPlayingIndex);
        m_localTable->setCurrentCell(-1,0);
    }
    int index = -1;
    for(int i=0;i < urlList.size();i++)
    {
        if(urlList.at(i)==content.canonicalUrl()){
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        m_curPlayingIndex = index;
        m_curPlayingDuration = m_localTable->item(index,1)->text();
        m_curPlayingVideoName = m_localTable->item(index,0)->text();

        m_localTable->setRowTextColor(m_curPlayingIndex,QColor(26,158,255));
        m_localTable->item(index,1)->setText(str_video_playing);

        m_localTable->setCurrentCell(index,0);
        m_localTable->setPlayingItemIndex(m_curPlayingIndex);
    }
    update();
}


void videoMiddleWidgetRight::addVideo()
{
    QFileDialog *dialog = new QFileDialog(mainwid,"selete file");
    if(dialog->exec()==QFileDialog::Accepted)
    {
        QStringList files = dialog->selectedFiles();
        if(files.isEmpty())
            return;
        for(int i=0;i<files.count();i++)
        {
            QFileInfo info(files[i]);
            if(!m_playList->getUrlList().contains(QUrl::fromLocalFile(files.value(i)))&&info.exists())
            {
                QString fileName=info.fileName();
                QString filePath=files.value(i);

                int rowCount = m_localTable->rowCount();
                insertIntoLocalTable(rowCount,fileName," ");
                m_playList->addToPlayList(filePath);
            }
        }
    }
}
