#include "musicwidgets.h"

#include <QVBoxLayout>
#include <QTime>
#include <QSettings>

#include "global_value.h"


musicWidgets::musicWidgets(QWidget *parent):baseWidget(parent)
{
    setObjectName("musicWidgets");
    setStyleSheet("#musicWidgets{border-image: url(:/image/music/music_bg.jpg);}"
                  "QLabel{color:white;}");
    initLayout();
    initConnection();
    initPlayerAndConnection();
    readSetting();
    setOriginData();
}

void musicWidgets::initLayout()
{
    baseWidget *m_mainwid =new baseWidget(this);
    QGridLayout *lyout=new QGridLayout;
    lyout->addWidget(m_mainwid);
    lyout->setContentsMargins(0,0,0,0);
    setLayout(lyout);

    m_topwid = new topWidgets(this);
    m_bottomwid = new bottomWidgets(this);
    m_middlewid = new middleWidgets(this);
    m_middlewid->setInitMainWidget(this);
    m_bottomwid->setInitMainWidget(this);

    QVBoxLayout *vlyout=new QVBoxLayout;
    vlyout->addWidget(m_topwid);
    vlyout->addWidget(m_middlewid);
    vlyout->addWidget(m_bottomwid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    m_mainwid->setLayout(vlyout);

    m_playmodewid=new playModeWidget(this);
    m_playmodewid->hide();
}

void musicWidgets::initConnection()
{
    connect(m_bottomwid->m_btnplaymode,SIGNAL(clicked(bool)),this,SLOT(slot_setPlayModeWidget()));
    connect(m_bottomwid->m_btnnext,SIGNAL(clicked(bool)),this,SLOT(slot_nextSong()));
    connect(m_bottomwid->m_btnprevious,SIGNAL(clicked(bool)),this,SLOT(slot_preSong()));
    connect(m_bottomwid->m_btnPlay,SIGNAL(clicked(bool)),this,SLOT(slot_playOrPause()));

    connect(m_playmodewid,SIGNAL(sig_CurrentModeChange(PlayMode)),this,SLOT(slot_setPlayMode(PlayMode)));
    connect(m_bottomwid->m_volwid,SIGNAL(sig_valueChanged(int)),this,SLOT(slot_volumeChanged(int)));
    connect(m_topwid->m_btnreturn,SIGNAL(clicked(bool)),this,SLOT(slot_setPause()));

    connect(m_middlewid->m_leftWid->m_Swidget0->m_table,SIGNAL(cellClicked(int,int)),this,SLOT(slot_itemDoubleClick(int,int)));
}

void musicWidgets::initPlayerAndConnection()
{
    m_player = new QMediaPlayer;

    // Media的状态发生改变，如从：可播放音乐变成不可播放音乐或者切换下一首歌曲等
    connect(m_player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(slot_onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    // Player控制器状态的改变,如从:播放状态编程暂停状态等 —  用于修改播放键按钮的样式
    connect(m_player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slot_onStateChanged(QMediaPlayer::State)));
    connect(m_player,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(slot_onCurrentMediaChanged(QMediaContent)));

    connect(m_player,SIGNAL(positionChanged(qint64)), this, SLOT(slot_onPositonChanged(qint64)));
    connect(m_player,SIGNAL(durationChanged(qint64)), this, SLOT(slot_onDuratuonChanged(qint64)));
}

void musicWidgets::setOriginData()
{
    m_bottomwid->setCurrentSongName(str_origin_move_songname);
}

void musicWidgets::readSetting()
{
    QSettings setting("config.ini",QSettings::IniFormat,0);
    setting.beginGroup("musicConfig");
    // 播放模式——单次，顺序，随机
    int playModeIndex=0;
    playModeIndex=setting.value("playmode").toInt();
    m_playmodewid->setCurrentMode(PlayMode(playModeIndex));
    // 音量
    int vol=setting.value("volume").toInt();
    if(vol==0)
        vol=80;
    m_player->setVolume(vol);
    m_bottomwid->m_volwid->m_slider_vol->setValue(m_player->volume());

    setting.endGroup();
}

void musicWidgets::slot_volumeChanged(int value)
{
    m_player->setVolume(value);
}

void musicWidgets::slot_setPlayModeWidget()
{
    if(!m_playmodewid->hasFocus())
    {
        m_playmodewid->setGeometry(m_bottomwid->m_btnplaymode->x()-(m_playmodewid->width()-m_bottomwid->m_btnplaymode->width())/2,
                                   m_topwid->height()+m_middlewid->height()-m_playmodewid->height()+m_bottomwid->m_btnplaymode->height(),
                                   150,150);
        m_playmodewid->setFocus();
        m_playmodewid->show();
    }
    else
    {
        m_playmodewid->hide();
    }
}

void musicWidgets::slot_onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::InvalidMedia)
    {
        qDebug()<<"InvalidMedia";
    }else if(status==QMediaPlayer::StalledMedia)
    {
        slot_nextSong();
    }else if(status==QMediaPlayer::EndOfMedia){
        slot_nextSong();
    }
}

void musicWidgets::slot_onStateChanged(QMediaPlayer::State state)
{
    if(state==QMediaPlayer::PlayingState)
    {
        m_bottomwid->setPauseStyle();
    }
    else
    {
        m_bottomwid->setPlayStyle();
    }
}

void musicWidgets::slot_onCurrentMediaChanged(QMediaContent content)
{
    m_middlewid->m_leftWid->m_Swidget0->updatePlayingItemStyle(content);
    m_bottomwid->setCurrentSongName(m_middlewid->m_leftWid->m_Swidget0->getCurPlayingSongName());
}

void musicWidgets::slot_onPositonChanged(qint64 position){
    int duration = m_player->duration();
    QTime totalTime(0, (duration/60000)%60, (duration/1000)%60);
    QTime currentTime(0, (position/60000)%60, (position/1000)%60);
    m_bottomwid->setPositionLabel(QString(currentTime.toString("mm:ss").append("/").append(totalTime.toString("mm:ss"))));
    m_bottomwid->m_mainslider->setValue(position);
}

void musicWidgets::slot_onDuratuonChanged(qint64 duration)
{
    m_bottomwid->m_mainslider->setRange(0,duration);
}

void musicWidgets::slot_setPlayMode(PlayMode mode)
{
    m_bottomwid->setPlayModeBtnStyle(PlayMode(mode));
    m_middlewid->m_leftWid->m_Swidget0->m_playlist->setPlayMode(mode);
}

void musicWidgets::slot_denyPlay()
{
    m_player->setMedia(m_onPlayUrl);
    m_player->play();
}

void musicWidgets::slot_itemDoubleClick(int row,int)
{
#ifdef DEVICE_EVB
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    QUrl url= playlist->mediaUrl(row);
    if(!url.isEmpty())
    {
        m_player->setMedia(url);
        m_player->play();
    }
#else
    m_player->setMedia(NULL);
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    m_onPlayUrl= playlist->mediaUrl(row);
    if(!m_onPlayUrl.isEmpty())
    {
        QTimer::singleShot(200,this,SLOT(slot_denyPlay()));
    }
#endif
}


void musicWidgets::slot_nextSong()
{
#ifdef DEVICE_EVB
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    if(playlist->getUrlList().size()>0){
        int curIndex = playlist->nextSong();
        m_player->setMedia(playlist->mediaUrl(curIndex));
        m_player->play();
    }
#else
    m_player->setMedia(NULL);
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    if(playlist->getUrlList().size()>0){
        int curIndex = playlist->nextSong();
        m_onPlayUrl = playlist->mediaUrl(curIndex);
        QTimer::singleShot(200,this,SLOT(slot_denyPlay()));
    }
#endif
}

void musicWidgets::slot_preSong()
{
#ifdef DEVICE_EVB
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    if(playlist->getUrlList().size()>0){
        int curIndex = playlist->preSong();
        m_player->setMedia(playlist->mediaUrl(curIndex));
        m_player->play();
    }
#else
    m_player->setMedia(NULL);
    mediaList *playlist = m_middlewid->m_leftWid->m_Swidget0->m_playlist;
    if(playlist->getUrlList().size()>0){
        int curIndex = playlist->preSong();
        m_onPlayUrl = playlist->mediaUrl(curIndex);
        QTimer::singleShot(200,this,SLOT(slot_denyPlay()));
    }
#endif
}

void musicWidgets::slot_playOrPause()
{

    if(m_player->state()==QMediaPlayer::PlayingState){
        m_player->pause();
    }
    else{
        if(m_player->isAudioAvailable()==true){
            m_player->play();
        }
    }
}

void musicWidgets::savaSetting()
{
    QSettings setting("config.ini",QSettings::IniFormat,0);

    setting.beginGroup("musicConfig");
    setting.setValue("playmode",m_middlewid->m_leftWid->m_Swidget0->m_playlist->getPlayMode());
    setting.setValue("volume",m_player->volume());
    setting.endGroup();
    m_player->pause();
}

void musicWidgets::slot_setPause()
{
    m_player->stop();
    m_player->setMedia(QMediaContent(NULL));
    setOriginData();
}

void musicWidgets::updateVolume(bool volumeAdd)
{
    if(volumeAdd){
        if(m_player->volume()<95)
        {
            m_player->setVolume(m_player->volume()+5);
        }
        else
        {
            m_player->setVolume(100);
        }
    }else{
        if(m_player->volume()>5)
        {
            m_player->setVolume(m_player->volume()-5);
        }
        else
        {
            m_player->setVolume(0);
        }
    }
    m_bottomwid->m_volwid->m_slider_vol->setValue(m_player->volume());
}
