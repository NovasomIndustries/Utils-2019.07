#include "cmessagebox.h"
#include <QHBoxLayout>
#include "global_value.h"

#ifdef DEVICE_EVB
int cbox_width = 400;
int cbox_height = 250;
#else
int cbox_width = 250;
int cbox_height = 150;

#endif

CMessageBox::CMessageBox(QWidget *parent):QDialog(parent)
  , m_eventLoop(NULL)
  , m_chooseResult(RESULT_CANCEL)
{
    this->setFixedSize(cbox_width,cbox_height);
    move((int)((parent->width()-width())/2),(int)((parent->height()-height())/2));
    this->setWindowFlags(Qt::Dialog);
    setStyleSheet("QDialog{border:1.5px solid rgb(0,120,215);background:rgb(43,43,43)}"
                  "QLabel{color:white}");
    initLayout();
    initConnection();
}

void CMessageBox::initLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_labelContent = new QLabel("",this);
    QFont font = m_labelContent->font();
    font.setPixelSize(font_size_big);
    font.setBold(true);
    m_labelContent->setFont(font);
    m_labelContent->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    // button layout
    QHBoxLayout *buttonlayout = new QHBoxLayout;
    m_btnConfirm = new CPushButton("",this);
    m_btnCancel = new CPushButton("",this);

    buttonlayout->addWidget(m_btnConfirm);
    buttonlayout->addWidget(m_btnCancel);
    buttonlayout->setSpacing(5);

    mainLayout->addWidget(m_labelContent);
    mainLayout->addLayout(buttonlayout);
    mainLayout->setSpacing(50);
    mainLayout->setMargin(20);
    setLayout(mainLayout);
}

void CMessageBox::initConnection()
{
    connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(slot_onConfirmClicked()));
    connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(slot_onCancelClicked()));
}

int CMessageBox::showCMessageBox(QWidget *parent,QString contentText, QString confirmText, QString cancelText)
{
    CMessageBox *messageBox = new CMessageBox(parent);
    messageBox->setBoxText(contentText,confirmText,cancelText);

    return messageBox->exec();
}

void CMessageBox::setBoxText(QString contentText, QString confirmText, QString cancelText)
{
    m_labelContent->setText(contentText);
    m_btnConfirm->setText(confirmText);
    m_btnCancel->setText(cancelText);
}

int CMessageBox::exec()
{
    this->setWindowModality(Qt::WindowModal);
    this->show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_chooseResult;
}

void CMessageBox::slot_onConfirmClicked()
{
    m_chooseResult = RESULT_CONFIRM;
    close();
}

void CMessageBox::slot_onCancelClicked()
{
    m_chooseResult = RESULT_CANCEL;
    close();
}

void CMessageBox::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
    event->accept();
}
