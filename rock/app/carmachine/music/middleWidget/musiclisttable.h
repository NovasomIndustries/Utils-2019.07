#ifndef MUISCLISTTABLE_H
#define MUISCLISTTABLE_H

#include <QObject>
#include <QTableWidget>

#include "musicitemgroupwidget.h"


class musicListTable:public QTableWidget
{
    Q_OBJECT
public:
    musicListTable(QWidget *parent=0);

    void setRowTextColor(int row, const QColor &color)const;
protected:
    void resize(int w, int h);
    void resizeEvent(QResizeEvent *event);
private:

    void init();
private slots:
    void slot_cellClicked(int,int);
signals:


};

#endif // MUISCLISTTABLE_H
