#ifndef CAMERATOPWIDGETS_H
#define CAMERATOPWIDGETS_H
#include <QLabel>
#include <basewidget.h>
#include "basepushbutton.h"


class cameraTopWidgets:public baseWidget
{
public:
    cameraTopWidgets(QWidget *parent = 0);

    FourStateButton *m_btnreturn;
    flatButton *m_btnicon;
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;

    QLabel *m_title;
private:
    void initWidget();
};

#endif // CAMERATOPWIDGETS_H
