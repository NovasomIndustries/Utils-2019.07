#ifndef VIDEOTOPWIDGETS_H
#define VIDEOTOPWIDGETS_H

#include "basepushbutton.h"
#include "basewidget.h"
#include <QLabel>

class videoTopWidgets:public baseWidget
{
public:    
    videoTopWidgets(QWidget *parent=0);

    FourStateButton *m_btnreturn;
    flatButton *m_btnicon;
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;

    void setPlayingVideoName(QString text){m_playingVideoName->setText(text);}
private:
    QLabel *m_playingVideoName;
    void initWidget();
};

#endif // VIDEOTOPWIDGETS_H
