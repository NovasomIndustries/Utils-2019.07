#ifndef VIDEOMIDDLEWIDGETRIGHT_H
#define VIDEOMIDDLEWIDGETRIGHT_H

#include "basewidget.h"
#include "listheader.h"
#include "videolocallisttable.h"
#include "videonetlisttable.h"
#include "player/videolist.h"

#include <QFileInfoList>
#include <QObject>
#include <QStackedWidget>
#include <QMediaContent>
#include <QEventLoop>

class videoMiddleWidgetRight:public baseWidget
{
    Q_OBJECT
public:
    videoMiddleWidgetRight(QWidget *parent=0);

    void updateResUi(QFileInfoList fileList);
    QFileInfoList findVideoFiles(const QString& path = QString(""));

    QString getCurrentVideoName(){return m_curPlayingVideoName;}
    videoList* getVideoList(){return m_playList;}
    void updatePlayingItemStyle(QMediaContent);
    void addVideo(); // 添加视频文件
    videoLocalListTable *m_localTable;
    void setOriginState();
private:
    listHeader *m_listHeader;
    QStackedWidget *m_stackedWid;
    videoNetListTable *m_netTable;
    // play list
    int m_curPlayingIndex;
    QString m_curPlayingDuration;
    QString m_curPlayingVideoName;
    videoList *m_playList;

    void initLayout();
    void initConnection();
    //    void getLocalListFromDataBase();

    void insertIntoLocalTable(int row,QString videoName,QString duration);

protected:

    //signals:
    //    sig_localTableItemDoubleClick(int,int);
private slots:
    void slot_switchToLocalList(){m_stackedWid->setCurrentIndex(0);}
    void slot_switchToNetList(){m_stackedWid->setCurrentIndex(1);}
};

#endif // VIDEOMIDDLEWIDGETRIGHT_H
