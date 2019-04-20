#include "funtiontablewidget.h"
#include <QDebug>
#include "global_value.h"

#ifdef DEVICE_EVB
int table_item_height = 80;
#else
int table_item_height = 50;
#endif

funtiontablewidget:: funtiontablewidget(QWidget *parent) : QTableWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setColumnCount(3);
    setRowCount(4);
    setShowGrid(false);

    verticalHeader()->setVisible(false);

    setMouseTracking(true);

    setStyleSheet("QTableView{background:transparent;}"
                  "QTableView::item:selected{color:white;background:rgb(32, 85, 130);}");

    setFrameShape(QFrame::NoFrame);
    setEditTriggers(QTableWidget::NoEditTriggers);
    setSelectionBehavior(QTableWidget::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::PointingHandCursor);

    m_previousColorRow = -1;
    m_defaultBkColor = QColor(32,38,51);

    connect(this, SIGNAL(cellEntered(int,int)), this,SLOT(listCellEntered(int,int)));
    connect(this, SIGNAL(cellClicked(int,int)), SLOT(listCellClicked(int,int)));
}

funtiontablewidget::~funtiontablewidget()
{

}

void funtiontablewidget::addFunctionItems(QStringList &normalicon, QStringList &selectedicon, QStringList &name)
{
    m_normalicon = normalicon;
    m_selectedicon = selectedicon;
    for(int i=0; i<rowCount(); ++i)
    {
        QTableWidgetItem *item = NULL;
        setItem(i, 0, item = new QTableWidgetItem());
        item = new QTableWidgetItem(QIcon(m_normalicon[i]), QString());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 1, item);
        item = new QTableWidgetItem(name[i]);
        item->setTextColor(QColor(255, 255, 255));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);
        setRowHeight(i,table_item_height);  //单元格高度
    }
}

void funtiontablewidget::listCellEntered(int row, int column)
{
    //还原之前鼠标滑过背景
    QTableWidgetItem *it = item(m_previousColorRow, 0);
    if(it != NULL)
    {
       setRowColor(m_previousColorRow, m_defaultBkColor);
    }

    it = item(row, column);
    if(it != NULL)
    {
       setRowColor(row, QColor(45,53,66));
    }
    m_previousColorRow = row;
}

void funtiontablewidget::listCellClicked(int row, int column)
{
    Q_UNUSED(column);
//    item(row, 1)->setTextColor(QColor(0,0,0));
    ChangeIcon(row);
    emit currentIndexChanged(row);
}

void funtiontablewidget::ChangeIcon(int currentrow)
{
    for(int row=0; row<rowCount(); row++)
    {
        QTableWidgetItem *it = item(row, 1);
        if(row == currentrow)
            it->setIcon(QIcon(m_selectedicon[row]));
        else
            it->setIcon(QIcon(m_normalicon[row]));
    }
}

void funtiontablewidget::setRowColor(int row, const QColor &color) const
{
    for(int col=0; col<columnCount(); col++)
    {
        QTableWidgetItem *it = item(row, col);
        it->setBackgroundColor(color);
    }
}

void funtiontablewidget::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    listCellEntered(-1, -1);
}

void funtiontablewidget::resizeEvent(QResizeEvent*)
{
#ifdef DEVICE_EVB
    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    headerview->resizeSection(0, 40);
    headerview->resizeSection(1, 70);
    headerview->resizeSection(2, width()-110);
#else
    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    headerview->resizeSection(0, 20);
    headerview->resizeSection(1, 40);
    headerview->resizeSection(2, width()-60);
#endif
}
