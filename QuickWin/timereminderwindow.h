#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TIMEREMINDERWINDOW_H
#define TIMEREMINDERWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QStyle>
#include <QDateTime>
#include <QMediaPlayer>
#include <QTimer>

namespace Ui {
class TimeReminderWindow;
}

class TimeReminderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeReminderWindow(QWidget *parent = nullptr);
    TimeReminderWindow(int ,int , QDateTime , QString , int , QString , QString , QString , QString , QWidget *parent = nullptr);
    ~TimeReminderWindow();

private:
    Ui::TimeReminderWindow *ui;
    QMediaPlayer *player;
    QTimer *timer;

public slots:
    void onTimeout();
};

#endif // TIMEREMINDERWINDOW_H
