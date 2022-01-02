#include "timereminderwindow.h"
#include "ui_timereminderwindow.h"

TimeReminderWindow::TimeReminderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeReminderWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
}

TimeReminderWindow::TimeReminderWindow(int remindType , int remindWeek , QDateTime dateTime , QString remindEvent , int remindDuration , QString remindSound, QString remindPic, QString remindRemarks , QString remindTimeStr ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeReminderWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setWindowTitle(remindEvent + " " + remindTimeStr);//ÉèÖÃ±êÌâ
    this->ui->labelEvent->setText(remindEvent);
    this->ui->labelRemarks->setText(remindRemarks);
    this->ui->labelTimeStr->setText(remindTimeStr);
    QImage *img = new QImage;
    img->load(remindPic);
    this->ui->labelPic->setPixmap(QPixmap::fromImage(*img));
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(remindSound));
    player->setVolume(30);
    player->play();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(remindDuration*1000);
}

TimeReminderWindow::~TimeReminderWindow()
{
    delete ui;
}

void TimeReminderWindow::onTimeout()
 {
     player->stop();
     delete player;
     player = NULL;
 }
