#ifndef MIDDLEWIDGETLEFT_H
#define MIDDLEWIDGETLEFT_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>

#include "basepushbutton.h"
#include "basewidget.h"
#include "middleLeftStackWidget0.h"
#include "middleLeftStackWidget1.h"
#include "middleLeftStackWidget2.h"

class musicWidgets;
class middleLeftStackWidget0;

class middleWidgetLeft : public baseWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_x READ getValue WRITE animation)

public:
    explicit middleWidgetLeft(QWidget *parent = 0);
    QStackedWidget  *m_stackwid;
    stackButton *m_btn[3];
    middleLeftStackWidget0 *m_Swidget0;
    middleLeftStackWidget1 *m_Swidget1;
    middleLeftStackWidget2 *m_Swidget2;

    static QColor color;//92 174 219
    static QColor bgcolor;

    void initLayout();
    void initAnimation();

    int getValue(){return m_x;}
    void animation(int i){m_x=i;update();}
    void setBackgroundtransparent();
    void setBackgroundnormal();
    void setDrawVerticalLine(bool is=true){m_isDrawVerticalLine=is;}
    void setInitMainWidgets(musicWidgets*);
protected:
    void paintEvent(QPaintEvent *);

    void resizeEvent(QResizeEvent*);

private slots:
    void slot_btn();
    void setWidgetOpacity(int);

    void slot_changeButtonSelected(int i);//改变选中图片

    void slot_finished(){m_isAnima=false;}
private:
    QPixmap m_pix;
    int m_index;
    int m_preindex;
    bool m_isDrawVerticalLine;
    bool m_isAnima;
    int m_x;
    int m_preItem;
    QPropertyAnimation *m_animation;
    QPropertyAnimation *m_Widanimation;

    musicWidgets *m_mainWid;
};


#endif // MIDDLEWIDGETLEFT_H
