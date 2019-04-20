#include "medialist.h"
#include <QTime>

mediaList::mediaList(QObject *parent):QObject(parent)
{
    m_musicindex=0;
    m_list.empty();
    setPlayMode(PlayMode::playInOrder);
}


void mediaList::setPlayMode(PlayMode playmode)
{
    if(playmode==PlayMode::playInOrder)
        m_playmode=0;
    if(playmode==PlayMode::playRandom)
        m_playmode=1;
    if(playmode==PlayMode::playOneCircle)
        m_playmode=2;
}

QUrl mediaList::mediaUrl(int index)
{
    if(m_list.isEmpty())
        return QUrl("");
    m_musicindex = index;
    return m_list.value(index);
}

int mediaList::nextSong()
{
    switch (m_playmode) {
    case 0://playInOrder
        if(m_musicindex+1>=m_list.count())
            m_musicindex=0;
        else
            m_musicindex++;
        break;

    case 1://playRandom
        QTime time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%m_list.count();
        m_musicindex=xxx;
        break;
    }
    return m_musicindex;
}

int mediaList::preSong()
{
    switch (m_playmode)
    {
    case 0://playInOrder
        if(m_musicindex==0)
            m_musicindex=0;
        else
            m_musicindex--;
        break;
    case 1://playRandom
        QTime time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%m_list.count();
        m_musicindex=xxx;
        break;
    }
    return m_musicindex;
}
