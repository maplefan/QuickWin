#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QMouseEvent>
#include <QStandardItem>

#include "iview.h"
#include "delegate.h"
class TableView : public QTableView, public IView {
    Q_OBJECT
private:
    int currHovered;
    void mouseMoveEvent(QMouseEvent *event);
    void disableMouseOver();
    void leaveEvent(QEvent *event);
public:    TableView(QWidget *parent = 0);
    void setMouseOver(const int);};
#endif // TABLEVIEW_H
