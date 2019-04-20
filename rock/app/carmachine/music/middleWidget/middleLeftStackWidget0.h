#ifndef MIDDLELEFTSTACKWIDGET0_H
#define MIDDLELEFTSTACKWIDGET0_H

#include <QObject>
#include <QLabel>

#include "basewidget.h"
#include "basepushbutton.h"
#include "player/medialist.h"
#include "player/mediadatabase.h"
#include "musiclisttable.h"

#include <QFileInfoList>
#include <QMenu>
#include <QMediaContent>
#include "musicwidgets.h"

class playListHeader:public baseWidget
{
    Q_OBJECT
public:
    explicit playListHeader(QWidget *parent);

    QLabel *m_listInfo;
private:
    flatButton *m_btnmenu;
    QMenu *m_menu;

    void initWidget();
    void initMenu();

signals:
    void sig_emptyList();
    void sig_addSong();
private slots:
    void slot_menuRequest(){m_menu->exec(QCursor::pos());}
};

class musicWidgets;

class middleLeftStackWidget0: public baseWidget
{
    Q_OBJECT
public:
    explicit middleLeftStackWidget0(QWidget *parent);

    void updateResUi(QFileInfoList fileList);
    QFileInfoList findMusicFiles(const QString& path);

    mediaList *m_playlist;
    // ui
    playListHeader *m_header;
    musicListTable *m_table;
    // method
    void initLayout();
    void initConnection();
    void addToPlayList(const QString &name,const QString &url,const QString &duration);
    void updateSongCountLabel();

    void setInitMainWidgets(musicWidgets*);
    void updatePlayingItemStyle(QMediaContent);
    QString getCurPlayingSongName(){return m_curPlayingSongName;}

private slots:
    void slot_addSong();
//    void slot_itemDoubleClick(int,int);
private:
    musicWidgets *m_mainwid;

    int m_curPlayingIndex;
    QString m_curPlayingDuration;
    QString m_curPlayingSongName;


};

#endif // MIDDLELEFTSTACKWIDGET0_H
