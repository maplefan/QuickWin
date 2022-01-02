#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "delegate.h"
#include <QDebug>
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 o = option;
    initStyleOption(&o, index);
    if ( o.state & QStyle::State_MouseOver )
    {
        view->setMouseOver(index.row());
    }
    o.state &= ~QStyle::State_MouseOver;
    QStyledItemDelegate::paint(painter, o, index);
}
