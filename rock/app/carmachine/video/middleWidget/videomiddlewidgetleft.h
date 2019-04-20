#ifndef VIDEOMIDDLEWIDGETLEFT_H
#define VIDEOMIDDLEWIDGETLEFT_H

#include "basewidget.h"
#include "videocontentwidget.h"
#include "videoslider.h"
#include "videoquickcontentwidget.h"
#include "videopositionwidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QQuickWidget>
#include <QMediaPlayer>


class videoMiddleWidgetLeft:public baseWidget
{
    Q_OBJECT
public:
    videoMiddleWidgetLeft(QWidget *parent);

    void addPositionWidget();
    void removePositionWidget();
    void onDurationChanged(qint64 duration);
    void onMediaPositionChanged(qint64);
    QMediaPlayer* getMediaPlayerFormQml(){return m_player;}
    videoQuickContentWidget* getContentWidget(){return m_contentWid;}
private:
    QVBoxLayout *vmainlyout;
    // mediaplayer类， 将传递给视频主界面videoWidgets做控制
    QMediaPlayer *m_player;

//    videoContentWidget *m_contentWid;
    videoQuickContentWidget *m_contentWid;

    videoPositionWidget *m_positionWid;

    void initLayout();
signals:
    void sig_sliderPositionChanged(int);
};

#endif // VIDEOMIDDLEWIDGETLEFT_H
