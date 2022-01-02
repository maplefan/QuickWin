#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TIMEREMINDER_H
#define TIMEREMINDER_H

#include <QMainWindow>
#include <QTreeView>
#include <QMenu>
#include <QTimer>
#include <QStandardItemModel>
#include "timereminddialog.h"

namespace Ui {
class TimeReminder;
}

class TimeReminder : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeReminder(QSystemTrayIcon *qsti ,QWidget *parent = nullptr);
    ~TimeReminder();
    QString getCountDown(qint64);

private:
    Ui::TimeReminder *ui;
    QMenu remindMenu;
    QTreeView *remindView;
    QStandardItemModel *remindModel;
    std::vector<ReminderInfo>ri;
    QTimer *timer;
    QAction *addAction;
    QAction *deleteAction;
    QAction *editAction;
    QItemSelectionModel * md;
    QSqlDatabase db;
    bool isStopUpdate;
    QSystemTrayIcon *qsti;

public slots:
    void slotTreeMenu(const QPoint &pos);
    void slotTreeMenuEdit();
    void slotTreeMenuDelete();
    void slotTreeMenuAdd();
    void getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString);
    void getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int);
    void onTimeout();
    void viewSelectCheck(const QItemSelection & selected, const QItemSelection & deselected);
};

#endif // TIMEREMINDER_H
