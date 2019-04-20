#ifndef GALLERYTOPWIDGETS_H
#define GALLERYTOPWIDGETS_H

#include "basewidget.h"
#include "basepushbutton.h"
#include <QLabel>

class galleryTopWidgets:public baseWidget
{
public:
    galleryTopWidgets(QWidget *parent);
    void updateTopTitle(QString title){m_titleLabel->setText(title);}
public:
    FourStateButton *m_btnreturn;
    flatButton *m_btnicon;
    flatButton *m_btnmobile;
    flatButton *m_btnsetting;
    flatButton *m_btnmini;
    flatButton *m_btnexit;

    QLabel *m_titleLabel;
private:
    void initWidget();
};

#endif // GALLERYTOPWIDGETS_H
