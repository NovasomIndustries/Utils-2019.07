#ifndef MUSICWIDGETS_H
#define MUSICWIDGETS_H
#include "basewidget.h"
#include "bottomWidget/bottomWidgets.h"
#include "topwidgets.h"
#include "middleWidget/middlewidgets.h"
#include "bottomWidget/playmodewidget.h"

#include <QMediaPlayer>

class middleWidgets;
class bottomWidgets;

class musicWidgets:public baseWidget
{
    Q_OBJECT
public:
    musicWidgets(QWidget *parent=0);

    topWidgets *m_topwid;
    bottomWidgets *m_bottomwid;
    middleWidgets *m_middlewid;

    playModeWidget *m_playmodewid;

    QMediaPlayer* getPlayer(){return m_player;}
    void savaSetting();
    void updateVolume(bool volumeAdd);
private:
    QMediaPlayer *m_player;

    QUrl m_onPlayUrl;

    void initLayout();
    void initConnection();
    void initPlayerAndConnection();
    void readSetting();
    void setOriginData();
private slots: 
    void slot_setPlayModeWidget();
    void slot_volumeChanged(int);

    void slot_setPlayMode(PlayMode);
    void slot_nextSong();
    void slot_preSong();
    void slot_playOrPause();
    void slot_setPause();
    // about player
    void slot_onMediaStatusChanged(QMediaPlayer::MediaStatus);
    void slot_onStateChanged(QMediaPlayer::State);
    void slot_onPositonChanged(qint64);
    void slot_onDuratuonChanged(qint64);

    void slot_itemDoubleClick(int,int);
    void slot_denyPlay();
public slots:
    void slot_onCurrentMediaChanged(QMediaContent);
protected:

};

#endif // MUSICWIDGETS_H
