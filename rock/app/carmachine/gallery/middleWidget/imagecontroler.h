#ifndef IMAGECONTROLER_H
#define IMAGECONTROLER_H

#include <QWidget>
#include <QPushButton>

class ImageControler:public QWidget
{
public:
    ImageControler(QWidget *parent = 0);

private:
    void initLayout();
public:
    QPushButton *m_btnLast;
    QPushButton *m_btnZoomOut;
    QPushButton *m_btnZoomIn;
    QPushButton *m_btnRotate;
    QPushButton *m_btnDetail;
    QPushButton *m_btnDelete;
    QPushButton *m_btnNext;
};

#endif // IMAGECONTROLER_H
