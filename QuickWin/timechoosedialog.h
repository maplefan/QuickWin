#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TIMECHOOSEDIALOG_H
#define TIMECHOOSEDIALOG_H

#include <QDialog>
#include <QTime>
#include <QDebug>
#include <QtMath>
#include "config.h"
#include "timereminderwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSystemTrayIcon>

struct ReminderInfo{
    int id;
    int remindType ;
    int remindWeek ;
    QDateTime dateTime ;
    QString remindEvent ;
    int remindDuration ;
    QString remindSound ;
    QString remindPic ;
    QString remindRemarks;
    QString remindTimeStr;
};

enum RemindTimeType
{
    DESIGNATEDDATE,
    EVERYYEAR,
    EVERYMONTH,
    EVERYDAY,
    EVERYWEEK,
};

namespace Ui {
class TimeChooseDialog;
}

class TimeChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeChooseDialog(QWidget *parent = nullptr);
    ~TimeChooseDialog();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

signals:
    void sendRemindTimeEveryDate(int ,int ,int ,QTime );
    void sendRemindTimeEveryYear(int , int , QTime);
    void sendRemindTimeEveryMonth(int , QTime);
    void sendRemindTimeEveryDay(QTime);
    void sendRemindTimeEveryWeek(int , QTime);

private:
    Ui::TimeChooseDialog *ui;
    int remindTimeType;
};

#endif // TIMECHOOSEDIALOG_H
