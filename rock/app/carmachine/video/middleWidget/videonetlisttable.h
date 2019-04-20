#ifndef VIDEONETLISTTABLE_H
#define VIDEONETLISTTABLE_H

#include <QTableWidget>

class videoNetListTable:public QTableWidget
{
public:
    videoNetListTable(QWidget *parent);
private:
    void init();
};

#endif // VIDEONETLISTTABLE_H
