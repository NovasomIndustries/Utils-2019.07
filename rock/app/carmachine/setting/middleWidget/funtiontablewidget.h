#ifndef FUNTIONTABLEWIDGET_H
#define FUNTIONTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QEvent>

class funtiontablewidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit funtiontablewidget(QWidget *parent = 0);
    ~funtiontablewidget();

protected:
    QColor m_defaultBkColor;
    int m_previousColorRow;
    QStringList m_normalicon;
    QStringList m_selectedicon;

    void resizeEvent(QResizeEvent*);

public:
    void addFunctionItems(QStringList &normalicon, QStringList &selectedicon, QStringList &name);
    void ChangeIcon(int currentrow);

protected:
    void setRowColor(int row, const QColor &color) const;
    void leaveEvent(QEvent *event);

signals:
    void currentIndexChanged(int index);

public slots:
    void listCellEntered(int row, int column);
    void listCellClicked(int row, int column);

};
#endif // FUNTIONTABLEWIDGET_H
