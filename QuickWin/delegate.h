#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>
#include "iview.h"
class Delegate : public QStyledItemDelegate {
private:
    IView *view;
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setView(IView *view) { this->view = view; }
};
#endif // DELEGATE_H
