#include "timereminddialog.h"
#include "ui_timereminddialog.h"

TimeRemindDialog::TimeRemindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeRemindDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("新增定时提醒"));
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    this->ui->editDuration->setValidator( validator );
    this->ui->pushButtonOK->setEnabled(false);
    remindType = 0;
    remindWeek = 0;
    isLastTime = true;
    isEditMode = false;
}

TimeRemindDialog::TimeRemindDialog(ReminderInfo ri , int index , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeRemindDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("新增定时提醒"));
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    this->ui->editDuration->setValidator( validator );
    this->ui->pushButtonOK->setEnabled(true);
    isLastTime = false;
    remindType = ri.remindType;
    remindWeek = ri.remindWeek;
    remindDateTime = ri.dateTime;
    this->ui->labelSoundPath->setText(ri.remindSound);
    this->ui->labelPicPath->setText(ri.remindPic);
    this->ui->textEditEvent->setText(ri.remindEvent);
    this->ui->editDuration->setText(QString::number(ri.remindDuration));
    this->ui->textEditRemark->setText(ri.remindRemarks);
    this->ui->labelRemindTime->setText(ri.remindTimeStr);
    isEditMode = true;
    editIndex = index;
}

TimeRemindDialog::~TimeRemindDialog()
{
    delete ui;
}

void TimeRemindDialog::on_pushButtonRemindTime_clicked()
{
    TimeChooseDialog *tcd = new TimeChooseDialog(this);
    connect(tcd , SIGNAL(sendRemindTimeEveryDate(int , int , int , QTime)) , this , SLOT(getRemindTimeEveryDate(int , int , int , QTime)));
    connect(tcd , SIGNAL(sendRemindTimeEveryYear(int , int , QTime)) , this , SLOT(getRemindTimeEveryYear(int , int , QTime)));
    connect(tcd , SIGNAL(sendRemindTimeEveryMonth(int , QTime)) , this , SLOT(getRemindTimeEveryMonth(int , QTime)));
    connect(tcd , SIGNAL(sendRemindTimeEveryDay(QTime)) , this , SLOT(getRemindTimeEveryDay(QTime)));
    connect(tcd , SIGNAL(sendRemindTimeEveryWeek(int , QTime)) , this , SLOT(getRemindTimeEveryWeek(int , QTime)));
    tcd->exec();

    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
       !isLastTime ){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::on_pushButtonSound_clicked()
{
    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
    QString file =  QFileDialog::getOpenFileName(this,tr("选择声音"),home,tr("所有 (*.*)"));
    if(file.isNull()) return;
    else{
        ui->labelSoundPath->setText(file);
        if(this->ui->textEditEvent->toPlainText().length() != 0 &&
           this->ui->editDuration->text().length() != 0 &&
           this->ui->labelRemindTime->text().length() != 0 &&
           this->ui->labelSoundPath->text().length() != 0 &&
           this->ui->labelPicPath->text().length() != 0 &&
                !isLastTime){
            this->ui->pushButtonOK->setEnabled(true);
        }
    }
}

void TimeRemindDialog::on_pushButtonPic_clicked()
{
    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
    QString file =  QFileDialog::getOpenFileName(this,tr("选择图片"),home,tr("图片 (*.png *.jpg)"));
    if(file.isNull()) return;
    else{
        ui->labelPicPath->setText(file);
        if(this->ui->textEditEvent->toPlainText().length() != 0 &&
           this->ui->editDuration->text().length() != 0 &&
           this->ui->labelRemindTime->text().length() != 0 &&
           this->ui->labelSoundPath->text().length() != 0 &&
           this->ui->labelPicPath->text().length() != 0 &&
                !isLastTime){
            this->ui->pushButtonOK->setEnabled(true);
        }
    }
}

void TimeRemindDialog::on_pushButtonReset_clicked()
{
    this->ui->textEditEvent->setText("");
    this->ui->editDuration->setText("");
    this->ui->labelRemindTime->setText("");
    this->ui->labelSoundPath->setText("");
    this->ui->labelPicPath->setText("");
    this->ui->textEditRemark->setText("");
    this->ui->pushButtonOK->setEnabled(false);
}

void TimeRemindDialog::on_pushButtonOK_clicked()
{
    QString remindEvent = this->ui->textEditEvent->toPlainText();
    int remindDuration = this->ui->editDuration->text().toInt();
    QString remindSound = this->ui->labelSoundPath->text();
    QString remindPic = this->ui->labelPicPath->text();
    QString remindRemarks = this->ui->textEditRemark->toPlainText();
    QString remindTimeStr = this->ui->labelRemindTime->text();
    if(isEditMode){
         sendRemindInfo(remindType , remindWeek , remindDateTime , remindEvent , remindDuration , remindSound , remindPic , remindRemarks , remindTimeStr , editIndex);
    }
    else{
         sendRemindInfo(remindType , remindWeek , remindDateTime , remindEvent , remindDuration , remindSound , remindPic , remindRemarks , remindTimeStr);
    }
    this->close();
}

void TimeRemindDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

void TimeRemindDialog::on_textEditEvent_textChanged()
{
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::on_editDuration_textChanged(const QString &arg1)
{
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::getRemindTimeEveryDate(int year , int month , int day , QTime time)
{
    qDebug()<<"getRemindTimeEveryDate";
    remindType = DESIGNATEDDATE;
    remindDateTime.setDate(QDate(year , month , day));
    remindDateTime.setTime(time);
    QDateTime currtime = QDateTime::currentDateTime();
    QDate date(year , month , day);
    QDateTime settime = QDateTime(date ,time);
    uint ctime = currtime.toTime_t();
    uint stime = settime.toTime_t();
    int ret = ctime - stime;
    if(ret >= 0 ){
        qDebug()<<ctime<<" "<<stime;
         this->ui->labelRemindTime->setText(tr("过去的时间:   ") + QString::number(year)+tr(" 年 ") + QString::number(month) + tr(" 月 ") + QString::number(day) + tr(" 日 ") + time.toString());
        isLastTime = true;
    }
    else{
         this->ui->labelRemindTime->setText(QString::number(year)+tr(" 年 ") + QString::number(month) + tr(" 月 ") + QString::number(day) + tr(" 日 ") + time.toString());
        isLastTime = false;
    }
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::getRemindTimeEveryYear(int month , int day , QTime time)
{
    qDebug()<<"getRemindTimeEveryYear";
    remindType = EVERYYEAR;
    remindDateTime.setDate(QDate( QDateTime::currentDateTime().date().year() , month , day));
    remindDateTime.setTime(time);
    qDebug()<<remindDateTime;
    isLastTime = false;
    this->ui->labelRemindTime->setText(tr("每年 ") + QString::number(month) + tr(" 月 ") + QString::number(day) + tr(" 日 ") + time.toString());
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::getRemindTimeEveryMonth(int day , QTime time)
{
    qDebug()<<"getRemindTimeEveryMonth";
    remindType = EVERYMONTH;
    remindDateTime.setDate(QDate(QDateTime::currentDateTime().date().year() , QDateTime::currentDateTime().date().month() , day));
    remindDateTime.setTime(time);
    qDebug()<<remindDateTime;
    isLastTime = false;
    this->ui->labelRemindTime->setText(tr("每月 ") + QString::number(day) + tr(" 日 ") + time.toString());
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::getRemindTimeEveryDay(QTime time)
{
    qDebug()<<"getRemindTimeEveryDay";
    remindType = EVERYDAY;
    remindDateTime.setDate(QDateTime::currentDateTime().date());
    remindDateTime.setTime(time);
    qDebug()<<remindDateTime;
    isLastTime = false;
    this->ui->labelRemindTime->setText(tr("每天 ") + time.toString());
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}

void TimeRemindDialog::getRemindTimeEveryWeek(int week , QTime time)
{
    qDebug()<<week;
    remindType = EVERYWEEK;
    remindDateTime.setDate(QDateTime::currentDateTime().date());
    remindDateTime.setTime(time);
    remindWeek = week;
    QString strWeek = "";
    if(week & 1){
        strWeek = strWeek + tr("星期一、");
    }
    if(week & 2){
        strWeek = strWeek + tr("星期二、");
    }
    if(week & 4){
        strWeek = strWeek + tr("星期三、");
    }
    if(week & 8){
        strWeek = strWeek + tr("星期四、");
    }
    if(week & 16){
        strWeek = strWeek + tr("星期五、");
    }
    if(week & 32){
        strWeek = strWeek + tr("星期六、");
    }
    if(week & 64){
        strWeek = strWeek + tr("星期天、");
    }
    isLastTime = false;
    this->ui->labelRemindTime->setText(tr("每周 ") + strWeek.mid(0,strWeek.length()-1) + " " + time.toString());;
    qDebug()<<"getRemindTimeEveryWeek";
    if(this->ui->textEditEvent->toPlainText().length() != 0 &&
       this->ui->editDuration->text().length() != 0 &&
       this->ui->labelRemindTime->text().length() != 0 &&
       this->ui->labelSoundPath->text().length() != 0 &&
       this->ui->labelPicPath->text().length() != 0 &&
            !isLastTime){
        this->ui->pushButtonOK->setEnabled(true);
    }
}
