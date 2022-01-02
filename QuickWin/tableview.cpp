#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "tableview.h"
#include <QDebug>
TableView::TableView(QWidget *parent) : QTableView(parent), currHovered(-1)
{
    Delegate *delegate = new Delegate;
    delegate->setView(this);
    setItemDelegate(delegate);
    setMouseTracking(true);
}

void TableView::setMouseOver(const int row)
{
    if ( row == currHovered) return;

    QStandardItemModel *_model = static_cast<QStandardItemModel*>(model());
    for ( int col = 0; col < _model->columnCount(); col++ )
    {
        QStandardItem *item = _model->item(row, col);
        QColor color(144,238,144);
        item->setBackground(QBrush(color));    }

    if ( currHovered != -1 )
    { disableMouseOver(); }
    currHovered = row;
}

void TableView::disableMouseOver()
{
    QStandardItemModel *_model = static_cast<QStandardItemModel*>(model());
    for ( int col = 0; col < _model->columnCount(); col++ )
    {
        QStandardItem *item = _model->item(currHovered, col);
        item->setBackground(QBrush(QColor("white")));
    }
}

void TableView::mouseMoveEvent(QMouseEvent *event)
{
    // TODO: you need know when mouse are not in table rect
    // then you need disable over
    QTableView::mouseMoveEvent(event);
}

void TableView::leaveEvent(QEvent *event){
    QStandardItemModel *_model = static_cast<QStandardItemModel*>(model());
    for ( int col = 0; col < _model->columnCount(); col++ )
    {
        QStandardItem *item = _model->item(currHovered, col);
        if(item != NULL){//注意为空的情况
            item->setBackground(QBrush(QColor("white")));
        }
    }

}
