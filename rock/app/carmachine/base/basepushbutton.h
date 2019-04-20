#ifndef BASEPUSHBUTTON_H
#define BASEPUSHBUTTON_H
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QList>
#include <QMouseEvent>
#include <QTimer>
#include <QSlider>
#include <QPainter>
#include <QRect>

// 扁平按钮
class flatButton : public QPushButton
{
    Q_OBJECT
public:
    flatButton(QWidget*parent=0);
    flatButton(const QString& str,QWidget*parent=0);
};

// 主界面导航按钮
class guideButton : public QPushButton
{
    Q_OBJECT
public:
    explicit guideButton(QString pixnormal,QString text,QWidget*parent);

protected:
//    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QPixmap  m_pix;
    QString m_text;
    bool m_enter;
};

// 四态图标
class FourStateButton:public QPushButton
{
    Q_OBJECT
public:
    FourStateButton(QString pix_listurl,QWidget*parent);
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QList<QPixmap> m_pixlist;
    int m_index;
    bool m_enter;
};


// 音乐声音按钮
class volButton:public QPushButton
{
    Q_OBJECT
public:
    volButton(const QString& normal,QWidget*parent=0);
    void setParentSlider(QSlider* slider){m_partnerslider=slider;}
protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
private:
    bool m_isenter;
    int m_savevol;
    int m_isvolempty;
    int m_index;
    QList<QPixmap> m_listnormal;
    QList<QPixmap> m_listhover;
    QList<QPixmap> m_listpressed;

    QSlider *m_partnerslider;
public slots:
    void setButtonPixmap(int);//getFromSlider
signals:
    void setMute(int);
};

// statck Button
class stackButton:public QPushButton
{
    Q_OBJECT
public:
    explicit stackButton(const QString& pixnormal,const QString& pixhover,const QString& pixsel,QWidget*parent);
    void setselected(bool=true);
protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
private:
    int m_index;
    bool m_enter;
    bool m_pressed;
    QPixmap m_pixnormal;
    QPixmap m_pixhover;
    QPixmap m_pixselected;
};




#endif // BASEPUSHBUTTON_H
