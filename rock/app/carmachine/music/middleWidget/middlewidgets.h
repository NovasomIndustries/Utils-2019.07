#ifndef MIDDLEWIDGETS_H
#define MIDDLEWIDGETS_H

#include <QObject>
#include <QWidget>
#include "basewidget.h"
#include "middlewidgetleft.h"
#include "middlewidgetright.h"

class middleWidgetLeft;
class musicWidgets;

class middleWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit middleWidgets(QWidget *parent = 0);
    void initLayout();

    middleWidgetLeft *m_leftWid;
    middleWidgetRight *m_rightWid;
    void setInitMainWidget(musicWidgets*);
private:
    musicWidgets *m_mainWid;

};

#endif // MIDDLEWIDGETS_H
