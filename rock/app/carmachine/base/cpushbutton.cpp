#include "cpushbutton.h"
#include "QLabel"
#include "global_value.h"

CPushButton::CPushButton(QString text,QWidget *parent):QPushButton(text,parent)
{
    QLabel *label = new QLabel;
    QFont font = label->font();
    font.setBold(true);
    setFont(font);
    setStyleSheet("QPushButton{background:rgb(85,85,85);color:white;}"
                  "QPushButton::hover{background:rgb(85,85,85);border:1px solid rgb(153,153,153)}"
                  "QPushButton::pressed{background:rgb(129,129,129)}");
}
