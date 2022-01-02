#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TIMEREMINDDIALOG_H
#define TIMEREMINDDIALOG_H

#include <QDialog>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QStandardPaths>
#include "timechoosedialog.h"

namespace Ui {
class TimeRemindDialog;
}

class TimeRemindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeRemindDialog(QWidget *parent = nullptr);
    TimeRemindDialog( ReminderInfo ri , int , QWidget *parent = nullptr);
    ~TimeRemindDialog();

private slots:
    void on_pushButtonRemindTime_clicked();

    void on_pushButtonSound_clicked();

    void on_pushButtonPic_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_textEditEvent_textChanged();

    void on_editDuration_textChanged(const QString &arg1);

    void getRemindTimeEveryDate(int year , int month , int day , QTime time);
    void getRemindTimeEveryYear(int month , int day , QTime time);
    void getRemindTimeEveryMonth(int day , QTime time);
    void getRemindTimeEveryDay(QTime time);
    void getRemindTimeEveryWeek(int week , QTime time);

signals:
    void sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString);
    void sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int);

private:
    Ui::TimeRemindDialog *ui;
    bool isLastTime;//是否是过去的时间
    bool isEditMode;//是否编辑模式
    int remindType;
    QDateTime remindDateTime;
    int remindWeek;
    int editIndex;
};

#endif // TIMEREMINDDIALOG_H
