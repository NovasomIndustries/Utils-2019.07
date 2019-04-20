#ifndef VIDEOBOTTOMWIDGETS_H
#define VIDEOBOTTOMWIDGETS_H

#include <basewidget.h>
#include "basepushbutton.h"
#include <music/bottomWidget/volwidget.h>

class videoBottomWidgets:public baseWidget
{
public:
    videoBottomWidgets(QWidget *parent=0);

    void setPlayingStyle();
    void setPauseStyle();

    flatButton *m_btnOpenFile;
    flatButton *m_btnPlayPause;
    flatButton *m_btnNext;
    flatButton *m_btnLast;
    volWidget *m_volWidget;


private:
    void initLayout();
};

#endif // VIDEOBOTTOMWIDGETS_H
