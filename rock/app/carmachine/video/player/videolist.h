#ifndef VIDEOLIST_H
#define VIDEOLIST_H

#include <QObject>
#include <QUrl>

class videoList:public QObject
{
    Q_OBJECT
public:
    videoList(QObject *parent = 0);
    void clearList(){m_list.clear();m_currentIndex=0;}

    inline void addToPlayList(const QString& path){m_list.append(QUrl::fromLocalFile(path));}
    QUrl getUrlAt(int index);
    QUrl getNextVideoUrl();
    QUrl getPreVideoUrl();
    QList<QUrl> getUrlList(){return m_list;}
private:
    QList<QUrl> m_list;  // 播放列表
    int m_currentIndex; // 当前播放曲目下标
};

#endif // VIDEOLIST_H
