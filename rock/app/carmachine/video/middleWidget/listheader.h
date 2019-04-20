#ifndef LISTHEADER_H
#define LISTHEADER_H

#include <basewidget.h>
#include <QObject>

#include <QLabel>

class funtionButton:public baseWidget
{
    Q_OBJECT
public:
    funtionButton(QString title,QWidget *parent);

    void setFousedStyle();
    void removeFouseStyle();
private:
    void initWidget();

    QLabel *m_title;
    QFrame *m_bottomLine;

    bool m_isCurItem;
protected:
    void mousePressEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
signals:
    void buttonClick();
};


// 列表的导航标识
class listHeader:public baseWidget
{
    Q_OBJECT
public:
    listHeader(QWidget *parent=0);
private:
    funtionButton *m_button1;
    funtionButton *m_button2;

    void initWidget();
public slots:
    void slot_onButtonLocalClick();
    void slot_onButtonNetClick();
signals:
    void buttonLocalClick();
    void buttonNetClick();
};

#endif // LISTHEADER_H
