#include "middleLeftStackWidget0.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMediaPlayer>
#include <QEventLoop>
#include <QTime>
#include <QDir>
#include <QFileDialog>
#include <QDirIterator>
#include "global_value.h"

#ifdef DEVICE_EVB
int header_height = 70;
int menu_width = 50;
#else
int header_height = 40;
int menu_width = 20;
#endif

QColor m_normalItemTextColor(48,48,48);
QColor m_PlayingItemTextColor(37,120,255);

middleLeftStackWidget0::middleLeftStackWidget0(QWidget*parent):baseWidget(parent)
{
    m_playlist = new mediaList(this);
    m_curPlayingIndex = -1;

    initLayout();
    initConnection();
}

void middleLeftStackWidget0::initLayout()
{
    QVBoxLayout *vlyout=new QVBoxLayout;

    m_header = new playListHeader(this);
    m_table = new musicListTable(this);

    vlyout->addWidget(m_header);
    vlyout->addWidget(m_table);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);

    setLayout(vlyout);
}

void middleLeftStackWidget0::initConnection()
{
    connect(m_header,SIGNAL(sig_addSong()),this,SLOT(slot_addSong()));

}

void middleLeftStackWidget0::setInitMainWidgets(musicWidgets *musicWidgets)
{
    this->m_mainwid = musicWidgets;
}

void middleLeftStackWidget0::addToPlayList(const QString &name,const QString &path,const QString &duration)
{
    int rowcount= m_table->rowCount();
    m_table->insertRow(rowcount);
    m_table->setItem(rowcount,1, new QTableWidgetItem(name));
    m_table->setItem(rowcount,2, new QTableWidgetItem(duration));
    m_table->item(rowcount,2)->setTextAlignment(Qt::AlignVCenter|Qt::AlignRight);

    m_playlist->addPlayList(path);

    updateSongCountLabel();
}

void middleLeftStackWidget0::updateSongCountLabel()
{
    m_header->m_listInfo->setText(str_song_list+QString("[%1]").arg(QString::number(m_table->rowCount())));
}

/**
 * @brief used to find all music file in path
 * @param path
 * @return
 */
QFileInfoList middleLeftStackWidget0::findMusicFiles(const QString& path)
{
    QFileInfoList musicFiles;

    QDirIterator it(path,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    while (it.hasNext())
    {
        QString name = it.next();
        QFileInfo info(name);
        if (info.isDir())
        {
            musicFiles.append(findMusicFiles(name));
        }
        else
        {
            if (info.suffix() == "mp3" || info.suffix() == "wave" || info.suffix() == "wma"
                    ||info.suffix() == "ogg" || info.suffix() == "midi" || info.suffix() == "ra"
                    ||info.suffix() == "mod")
            {
                musicFiles.append(info);
            }
        }
    }
    return musicFiles;
}


void middleLeftStackWidget0::updateResUi(QFileInfoList fileList)
{
    for(int i = m_table->rowCount();i > 0;i--)
    {
        m_table->removeRow(0);
    }
    m_playlist->clearList();
    updateSongCountLabel();

    for(int i=0;i<fileList.size();i++){
        QFileInfo fileInfo = fileList.at(i);
        if(!m_playlist->getUrlList().contains(QUrl::fromLocalFile(fileInfo.absoluteFilePath()))){
            addToPlayList(fileInfo.baseName(),fileInfo.absoluteFilePath()," ");
        }
    }
    m_curPlayingIndex = -1;
}


void middleLeftStackWidget0::slot_addSong()
{
    QFileDialog *dialog = new QFileDialog(mainwid,"Selete File");
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    if(dialog->exec()==QFileDialog::Accepted)
    {
        QStringList files = dialog->selectedFiles();
        if(files.isEmpty())
            return;
        for(int i=0;i<files.count();i++)
        {
            QFileInfo info(files[i]);
            if(!m_playlist->getUrlList().contains(QUrl::fromLocalFile(files.value(i)))&&info.exists())
            {
                QString m_name=info.baseName();
                addToPlayList(m_name,files.at(i)," ");
            }
        }
    }
}


void middleLeftStackWidget0::updatePlayingItemStyle(QMediaContent content)
{
    QList<QUrl> urlList = m_playlist->getUrlList();
    if(m_curPlayingIndex!=-1)
    {
        m_table->item(m_curPlayingIndex,2)->setText(m_curPlayingDuration);
        m_table->setRowTextColor(m_curPlayingIndex,m_normalItemTextColor);

        m_table->setCurrentCell(-1,0);
        m_curPlayingIndex = -1;
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
        m_curPlayingDuration = m_table->item(index,2)->text();
        m_curPlayingSongName = m_table->item(index,1)->text();

        m_table->setRowTextColor(m_curPlayingIndex,m_PlayingItemTextColor);
        m_table->item(index,2)->setText(str_song_playing);

        m_table->setCurrentCell(index,0);
    }
}


playListHeader::playListHeader(QWidget*parent):baseWidget(parent)
{
    setFixedHeight(header_height);
    setStyleSheet("background:rgb(240,240,240)");
    setCursor(Qt::PointingHandCursor);
    initWidget();
    initMenu();
}

void playListHeader::initWidget()
{
    QHBoxLayout *lyout=new QHBoxLayout;

    m_listInfo=new QLabel(str_song_list+"[0]",this);

    m_btnmenu=new flatButton(this);
    m_btnmenu->setFixedSize(menu_width,menu_width);
    m_btnmenu->setStyleSheet("QPushButton{border-image:url(:/image/music/indicator_menu (1).png);}"
                             "QPushButton:hover{border-image:url(:/image/music/indicator_menu (2).png);}"
                             "QPushButton:pressed{border-image:url(:/image/music/indicator_menu (3).png);}");

    lyout->addSpacing(10);
    lyout->addWidget(m_listInfo,0,Qt::AlignVCenter);
    lyout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
    lyout->addWidget(m_btnmenu,0,Qt::AlignVCenter);
    lyout->addSpacing(14);
    lyout->setContentsMargins(0,0,0,0);
    lyout->setSpacing(2);
    setLayout(lyout);
}

void playListHeader::initMenu()
{
    m_menu=new QMenu;
    QAction *act_addsong=new QAction(str_add_song,m_menu);
    //    QAction* act_emptyList=new QAction(str_clear_list,m_menu);

    m_menu->addAction(act_addsong);
    //    m_menu->addAction(act_emptyList);
    m_menu->addAction(new QAction("1111",m_menu));
    m_menu->addAction(new QAction("2222",m_menu));
    m_menu->addAction(new QAction("3333",m_menu));

    connect(act_addsong,SIGNAL(triggered(bool)),this,SIGNAL(sig_addSong()));
    //    connect(act_emptyList,SIGNAL(triggered(bool)),this,SIGNAL(sig_emptyList()));

    connect(m_btnmenu,SIGNAL(clicked(bool)),this,SLOT(slot_menuRequest()));
}
