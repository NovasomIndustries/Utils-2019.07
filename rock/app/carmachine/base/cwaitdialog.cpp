#include "cwaitdialog.h"
#include "global_value.h"

#include "QHBoxLayout"
#include <QLabel>

CWaitDialog::CWaitDialog(QString waitText,QWidget *parent)
    :QDialog(parent)
{
    m_waitText = waitText;
    initWidget();
}

void CWaitDialog::initWidget()
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_indecator = new QProgressIndicator(this);
    m_indecator->setFixedSize(150,150);
    m_indecator->setColor(Qt::black);
    m_indecator->startAnimation();

    QLabel *label = new QLabel(m_waitText,this);
    label->setAlignment(Qt::AlignHCenter);
    QFont font = label->font();
    font.setPixelSize(font_size_big);
    font.setBold(true);
    label->setFont(font);

    layout->addWidget(m_indecator);
    layout->addWidget(label);

    setLayout(layout);
}
