#ifndef BOTTOMWIDGETS_H
#define BOTTOMWIDGETS_H

#include <QObject>
#include <QWidget>
#include <QLabel>

#include "basewidget.h"
#include "basepushbutton.h"
#include "myslider.h"
#include "TextMovingWidget.h"
#include "volwidget.h"
#include "musicwidgets.h"
#include "player/medialist.h"

class musicWidgets;

class bottomWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit bottomWidgets(QWidget *parent = 0);
    void init();
    void setRandomStyle();
    void setInOrderStyle();
    void setOneCycleStyle();
    void setPlayModeBtnStyle(PlayMode);
    void setPauseStyle();
    void setPlayStyle();
    void setBufferStaus();
    void setInitMainWidget(musicWidgets *m){m_mainWid=m;}

    void setCurrentSongName(const QString&);
    void setPositionLabel(const QString&);

    flatButton *m_btnnext;
    flatButton *m_btnprevious;
    flatButton *m_btnPlay;

    mySlider *m_mainslider;

    flatButton *m_btnlrc;
    volWidget *m_volwid;
    flatButton *m_btnplaymode;
protected:
    bool eventFilter(QObject *, QEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
signals:

public slots:

private:
    musicWidgets *m_mainWid;
    QLabel *m_labposition;
    TextMovingWidget *m_labnowPlayname;
};

#endif // bottomWidgets_H
