#include "wlanlisttable.h"

#include <QHeaderView>
#include <QScrollBar>
#include "global_value.h"

#ifdef DEVICE_EVB
int wlan_item_height = 50;
#else
int wlan_item_height = 30;
#endif

wlanListTable::wlanListTable(QWidget *parent):QTableWidget(parent)
{
    init();
    initConnection();
}

void wlanListTable::init()
{
    m_previousFousedRow = -1;
    m_playingItemRow = -1;

    setMouseTracking(true);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::NoFrame);
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    setShowGrid(false);       //隐藏线
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    setEditTriggers(QTableWidget::NoEditTriggers);  // 设置表格不可编辑
    setSelectionBehavior (QAbstractItemView::SelectRows); //设置点击选取行
    setSelectionMode (QAbstractItemView::SingleSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);

    insertColumn(0);
    insertColumn(1);
    insertColumn(2);
    insertColumn(3);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);


    verticalHeader()->setDefaultSectionSize(wlan_item_height);//设置默认item高度

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;margin: 0px 2px 0px 0px;}"
                                       "QScrollBar::handle{background:rgb(217,217,217);border-radius:4px;}"
                                       "QScrollBar::handle:hover{background: rgb(191,191,191);}"
                                       "QScrollBar::add-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::sub-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");

    setStyleSheet("QTableWidget{background:rgb(27,29,36)}"
                  "QTableWidget{color:rgb(255,255,255);}"
                  "QTableWidget::item:selected{background:rgb(27,29,36);}"
                  "QTableWidget::item{selection-color:rgb(255,255,255);}");

#ifdef DEVICE_EVB
    QFont font = this->font();
    font.setPixelSize(font_size-5);
    setFont(font);
#else

#endif
}

void wlanListTable::initConnection()
{
    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(slot_cellEnter(int,int)));
}

void wlanListTable::slot_cellEnter(int row,int column)
{
    //    QTableWidgetItem *it = item(m_previousFousedRow,0);
    //    // 还原上次选中的item
    //    if(it != NULL)
    //    {
    //        if(m_playingItemRow!=m_previousFousedRow){
    //            setRowTextColor(m_previousFousedRow,QColor(255,255,255));
    //        }
    //    }
    //    // 设置当前选中item的字体颜色
    //    it = item(row, column);
    //    if(it != NULL)
    //    {
    //        setRowTextColor(row,QColor(26,158,255));
    //    }
    //    m_previousFousedRow = row;
}

void wlanListTable::setRowTextColor(int row, const QColor &color)const
{
    //    for(int col=0; col<columnCount(); col++)
    //    {
    //        QTableWidgetItem *it = item(row, col);
    //        it->setTextColor(color);
    //    }
}

void wlanListTable::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    slot_cellEnter(-1, -1);
}

void wlanListTable::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidget::mouseMoveEvent(event);
    // 不在格子上移动
    if(itemAt(mapFromGlobal(QCursor::pos()))==Q_NULLPTR)
    {
        slot_cellEnter(-1,-1);
    }
}

void wlanListTable::resizeEvent(QResizeEvent *event)
{
#ifdef DEVICE_EVB
    QTableWidget::resizeEvent(event);
    horizontalHeader()->resizeSection(0,width()-470);
    horizontalHeader()->resizeSection(1,210);
    horizontalHeader()->resizeSection(2,60);
    horizontalHeader()->resizeSection(3,200);
#else
    QTableWidget::resizeEvent(event);
    horizontalHeader()->resizeSection(0,width()-290);
    horizontalHeader()->resizeSection(1,120);
    horizontalHeader()->resizeSection(2,20);
    horizontalHeader()->resizeSection(3,150);
#endif
}

