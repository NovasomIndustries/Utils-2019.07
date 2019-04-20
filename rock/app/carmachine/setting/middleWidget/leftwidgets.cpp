#include "leftwidgets.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "global_value.h"

leftWidgets::leftWidgets(QWidget *parent):baseWidget(parent)
{
    setStyleSheet("QWidget{background:rgb(32,38,51)}");
    initLayout();
}

void leftWidgets::initLayout()
{
    m_funtionlist = new funtiontablewidget(this);
    m_funtionlist->setRowCount(2);
    QStringList normaliconlist,selectediconlist,namelist;
    normaliconlist.append(":/image/setting/wifi_normal.png");
    normaliconlist.append(":/image/setting/bt_normal.png");
//    normaliconlist.append(":/image/setting/common_normal.png");
//    normaliconlist.append(":/image/setting/system_normal.png");
    selectediconlist.append(":/image/setting/wifi_seleted.png");
    selectediconlist.append(":/image/setting/bt_seleted.png");
//    selectediconlist.append(":/image/setting/common_seleted.png");
//    selectediconlist.append(":/image/setting/system_seleted.png");
    namelist.append(str_net_manager);
    namelist.append(str_bt_manager);
//    namelist.append(str_common_setting);
//    namelist.append(str_system_setting);
    m_funtionlist->addFunctionItems(normaliconlist,selectediconlist,namelist);


    QVBoxLayout *vmainlyout = new QVBoxLayout;
    vmainlyout->addWidget(m_funtionlist);
    vmainlyout->setContentsMargins(0,0,0,0);

    setLayout(vmainlyout);
}
