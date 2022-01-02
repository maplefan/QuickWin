#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef QUICKSTOCK_H
#define QUICKSTOCK_H

#include <QMainWindow>
#include <vector>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QMenu>
#include <QTextCodec>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include "CStockSignal.h"
#include "config.h"
#include "addstockdialog.h"
#include "stockreminddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QuickStock; }
QT_END_NAMESPACE

struct stockRemind{
    QString stockCode ;
    QString info ;
    QString data ;
};

class QuickStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit  QuickStock(QSystemTrayIcon *qsti , QWidget *parent = nullptr);
    ~QuickStock();
    void dealStockInfo(QString stockData , QString stockInfo);
    void closeEvent(QCloseEvent *event);
    void dealStockInfo();
    void firstDealStockInfo();

private:
    std::vector<stockRemind>sr;
    Ui::QuickStock *ui;
    CStockSignal m_signal;
    QTimer timer;
    QMenu *m_stockMenu;
    QStandardItemModel *model;
    QModelIndex selectIndex;
    QStringList stockList;
    QStringList stockInfoList;
    QString stockConfig;
    QSystemTrayIcon *qsti;
    int stockShow;

private slots:
    void OnTimerout();
    void getStockData(QString stockData , QString stockInfo);
    //右键菜单响应函数
    void slotContextMenu(QPoint pos);
    void slot_itemToTop();
    void slot_addItem();
    void slot_deleteItem();
    void slot_open();
    void slot_remind();
    void recvAddStockDialogData(QString data);
    void recvStockRemindDialogData(QString stockCode , QString info , QString data);
};
#endif // QUICKSTOCK_H
