#include "timechoosedialog.h"
#include "ui_timechoosedialog.h"

TimeChooseDialog::TimeChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeChooseDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("选择提醒时间"));
    this->ui->widgetDate->setVisible(true);
    this->ui->widgetEveryYear->setVisible(false);
    this->ui->widgetEveryMonth->setVisible(false);
    this->ui->widgetEveryDay->setVisible(false);
    this->ui->widgetEveryWeek->setVisible(false);
    remindTimeType = DESIGNATEDDATE;
    QRegExp regxMonth("^(0?[1-9]|1[0-2])$");
    QRegExp regxDay("^(0?[1-9]|[1-2]\\d|3[0-1])$");
    QValidator *validatorMonth = new QRegExpValidator(regxMonth, this );
    QValidator *validatorDay = new QRegExpValidator(regxDay, this );
    this->ui->lineEditMonth->setValidator(validatorDay);
    this->ui->lineEditYear->setValidator(validatorMonth);
    this->ui->lineEditYear2->setValidator(validatorDay);
    QDateTime datetime = QDateTime::currentDateTime();
    this->ui->timeEdit->setDateTime(datetime);
    this->ui->dateEdit->setDateTime(datetime);
}

TimeChooseDialog::~TimeChooseDialog()
{
    delete ui;
}

void TimeChooseDialog::on_comboBox_currentIndexChanged(int index)
{
    if(index == DESIGNATEDDATE){
        this->ui->widgetDate->setVisible(true);
        this->ui->widgetEveryYear->setVisible(false);
        this->ui->widgetEveryMonth->setVisible(false);
        this->ui->widgetEveryDay->setVisible(false);
        this->ui->widgetEveryWeek->setVisible(false);
        remindTimeType = DESIGNATEDDATE;
    }
    else if(index == EVERYYEAR){
        this->ui->widgetDate->setVisible(false);
        this->ui->widgetEveryYear->setVisible(true);
        this->ui->widgetEveryMonth->setVisible(false);
        this->ui->widgetEveryDay->setVisible(false);
        this->ui->widgetEveryWeek->setVisible(false);
        remindTimeType = EVERYYEAR;
    }
    else if(index == EVERYMONTH){
        this->ui->widgetDate->setVisible(false);
        this->ui->widgetEveryYear->setVisible(false);
        this->ui->widgetEveryMonth->setVisible(true);
        this->ui->widgetEveryDay->setVisible(false);
        this->ui->widgetEveryWeek->setVisible(false);
        remindTimeType = EVERYMONTH;
    }
    else if(index == EVERYDAY){
        this->ui->widgetDate->setVisible(false);
        this->ui->widgetEveryYear->setVisible(false);
        this->ui->widgetEveryMonth->setVisible(false);
        this->ui->widgetEveryDay->setVisible(true);
        this->ui->widgetEveryWeek->setVisible(false);
        remindTimeType = EVERYDAY;
    }
    else if(index == EVERYWEEK){
        this->ui->widgetDate->setVisible(false);
        this->ui->widgetEveryYear->setVisible(false);
        this->ui->widgetEveryMonth->setVisible(false);
        this->ui->widgetEveryDay->setVisible(false);
        this->ui->widgetEveryWeek->setVisible(true);
        remindTimeType = EVERYWEEK;
    }
}

void TimeChooseDialog::on_buttonBox_accepted()
{
    QTime time = this->ui->timeEdit->time();
    //int hour = this->ui->timeEdit->time().hour();
    //int minute = this->ui->timeEdit->time().minute();

    if(remindTimeType == DESIGNATEDDATE){
        int year = this->ui->dateEdit->date().year();
        int month = this->ui->dateEdit->date().month();
        int day = this->ui->dateEdit->date().day();
        emit sendRemindTimeEveryDate(year , month , day , time);
    }
    else if(remindTimeType == EVERYYEAR){
        int month = this->ui->lineEditYear->text().toInt();
        int day = this->ui->lineEditYear2->text().toInt();
        emit sendRemindTimeEveryYear(month , day, time);
    }
    else if(remindTimeType == EVERYMONTH){
        int day = this->ui->lineEditMonth->text().toInt();
        emit sendRemindTimeEveryMonth(day , time );
    }
    else if(remindTimeType == EVERYDAY){
        emit sendRemindTimeEveryDay(time);
    }
    else if(remindTimeType == EVERYWEEK){
        int week = 0;
        if(this->ui->checkBox_1->isChecked()){
            week = week | 1;
        }
        if(this->ui->checkBox_2->isChecked()){
            week = week | 2;
        }
        if(this->ui->checkBox_3->isChecked()){
            week = week | 4;
        }
        if(this->ui->checkBox_4->isChecked()){
            week = week | 8;
        }
        if(this->ui->checkBox_5->isChecked()){
            week = week | 16;
        }
        if(this->ui->checkBox_6->isChecked()){
            week = week | 32;
        }
        if(this->ui->checkBox_7->isChecked()){
            week = week | 64;
        }
        emit sendRemindTimeEveryWeek(week , time);
    }
}
