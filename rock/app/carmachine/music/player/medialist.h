#ifndef MEDIALIST_H
#define MEDIALIST_H
#include<QUrl>
#include <QObject>

enum PlayMode{playInOrder=0,playRandom=1,playOneCircle=2};
class mediaList:public QObject
{
    Q_OBJECT
public:
    mediaList(QObject *parent = 0);

    void clearList(){m_list.clear();m_musicindex=0;}

    void setPlayMode(PlayMode);
    int getPlayMode(){return m_playmode;}
    inline void addPlayList(const QString& path){m_list.append(QUrl::fromLocalFile(path));}
    QUrl mediaUrl(int index);
    int nextSong();
    int preSong();
    QList<QUrl> getUrlList(){return m_list;}

private:
    QList<QUrl> m_list;  // 播放列表
    int m_musicindex; // 当前播放曲目下标
    int m_playmode;   // 当前播放循环方式
};

#endif // MEDIALIST_H
