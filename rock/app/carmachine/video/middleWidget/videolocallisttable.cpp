#include "videolocallisttable.h"

#include <QHeaderView>
#include <QScrollBar>

#include "global_value.h"

#ifdef DEVICE_EVB
int video_item_height = 90;
#else
int video_item_height = 35;
#endif

QLineDelegate::QLineDelegate(QTableView* tableView)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor, 0, tableView->gridStyle());
    view = tableView;
}
void QLineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    QStyledItemDelegate::paint(painter, option, index);
    QPen oldPen = painter->pen();
    painter->setPen(pen);
    //painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->setPen(oldPen);
}

videoLocalListTable::videoLocalListTable(QWidget *parent):QTableWidget(parent)
{
    init();
    initConnection();
}

void videoLocalListTable::init()
{
    m_previousFousedRow = -1;
    m_playingItemRow = -1;

    QFont listFont = this->font();
    listFont.setPixelSize(font_size_big);
    this->setFont(listFont);

    setMouseTracking(true);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::NoFrame);
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    setShowGrid(false);
    setItemDelegate(new QLineDelegate(this));
    setEditTriggers(QTableWidget::NoEditTriggers);
    setSelectionBehavior (QAbstractItemView::SelectRows);
    setSelectionMode (QAbstractItemView::SingleSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAcceptDrops(true);

    insertColumn(0);
    insertColumn(1);

    QHeaderView *horizontalHeader =  this->horizontalHeader();
    horizontalHeader->setVisible(true);
    horizontalHeader->setDefaultAlignment(Qt::AlignLeft);
    QFont headerFont = horizontalHeader->font();
    headerFont.setPixelSize(font_size_big);
    horizontalHeader->setFont(headerFont);
    horizontalHeader->setHighlightSections(false);
    horizontalHeader->setStyleSheet("QHeaderView::section{background-color:rgba(150,150,150,0)}");

    verticalHeader()->setVisible(false);
    verticalHeader()->setDefaultSectionSize(video_item_height);

    QStringList header;
    header<<tr("视频播放列表")<<tr(" ");
    setHorizontalHeaderLabels(header);

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;margin: 0px 2px 0px 0px;}"
                                       "QScrollBar::handle{background:rgb(217,217,217);border-radius:4px;}"
                                       "QScrollBar::handle:hover{background: rgb(191,191,191);}"
                                       "QScrollBar::add-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::sub-line:vertical{border:1px rgb(230,230,230);height: 1px;}"
                                       "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");

    setStyleSheet("QTableWidget{background:transparent}"
                  "QTableWidget{color:rgb(255,255,255);}"
                  "QTableWidget::item:selected{background:rgb(43,45,51);}"
                  "QTableWidget::item{selection-color:rgb(26,158,255);}"
                  );
}

void videoLocalListTable::initConnection()
{
    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(slot_cellEnter(int,int)));
}

void videoLocalListTable::slot_cellEnter(int row,int column)
{
    QTableWidgetItem *it = item(m_previousFousedRow,0);
    // 还原上次选中的item
    if(it != NULL)
    {
        if(m_playingItemRow!=m_previousFousedRow){
            setRowTextColor(m_previousFousedRow,QColor(255,255,255));
        }
    }
    // 设置当前选中item的字体颜色
    it = item(row, column);
    if(it != NULL)
    {
        setRowTextColor(row,QColor(26,158,255));
    }
    m_previousFousedRow = row;
}

void videoLocalListTable::setRowTextColor(int row, const QColor &color)const
{
    for(int col=0; col<columnCount(); col++)
    {
        QTableWidgetItem *it = item(row, col);
        it->setTextColor(color);
    }
}

void videoLocalListTable::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    slot_cellEnter(-1, -1);
}

void videoLocalListTable::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidget::mouseMoveEvent(event);
    // 不在格子上移动
    if(itemAt(mapFromGlobal(QCursor::pos()))==Q_NULLPTR)
    {
        slot_cellEnter(-1,-1);
    }
}

void videoLocalListTable::resizeEvent(QResizeEvent *)
{
#ifdef DEVICE_EVB
    horizontalHeader()->resizeSection(0,width()-120);
    horizontalHeader()->resizeSection(1,120);
#else
    horizontalHeader()->resizeSection(0,width()-80);
    horizontalHeader()->resizeSection(1,80);
#endif
}
