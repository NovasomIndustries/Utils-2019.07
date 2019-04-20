#include "videonetlisttable.h"
#include <QHeaderView>
#include <QScrollBar>

videoNetListTable::videoNetListTable(QWidget *parent):QTableWidget(parent)
{
    init();
}

void videoNetListTable::init()
{
    setMouseTracking(true);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::NoFrame);
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 水平滚动条禁用
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    setShowGrid(false);       //隐藏线
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    setEditTriggers(QTableWidget::NoEditTriggers);  // 设置表格不可编辑
    setSelectionBehavior (QAbstractItemView::SelectRows); //设置点击选取行
    setSelectionMode (QAbstractItemView::SingleSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    insertColumn(0);
    insertColumn(1);
    insertColumn(2);
    insertColumn(3);
    verticalHeader()->setDefaultSectionSize(32);//设置默认item高度的32

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;margin: 0px 2px 0px 0px;}"
                                       "QScrollBar::handle{background:rgb(217,217,217);border-radius:4px;}"
                                       "QScrollBar::handle:hover{background: rgb(191,191,191);}"
                                       "QScrollBar::add-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::sub-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");

    setStyleSheet("QTableWidget{background:transparent}"
                  "QTbaleWidget{background:yellow}"
                  "QTableWidget{color:rgb(48,48,48);}"
                  "QTableWidget::item:selected{background:rgb(180,180,180,100);}"
                  "QTableWidget::item{selection-color:rgb(37,120,255);}");
    //    setFont(QFont("Microsoft YaHei",10,QFont::Normal));
}
