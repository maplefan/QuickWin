#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "stockreminddialog.h"
#include "ui_stockreminddialog.h"

StockRemindDialog::StockRemindDialog(QString stockList , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockRemindDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setWindowTitle(tr("设置提醒"));

    QRegExp regx("^([0-9]{1,}[.][0-9]*)$");//仅可以输入数字
    QValidator *validatorFall = new QRegExpValidator(regx, ui->lineEditFall );
    ui->lineEditFall->setValidator( validatorFall );

    QValidator *validatorRise = new QRegExpValidator(regx, ui->lineEditRise );
    ui->lineEditRise->setValidator( validatorRise );

    QValidator *validatorRate = new QRegExpValidator(regx, ui->lineEditRate );
    ui->lineEditRate->setValidator( validatorRate );

    QStringList stockInfo = stockList.split("~");
    qDebug()<<stockInfo[0];
    qDebug()<<stockInfo[1];
    qDebug()<<stockInfo[2];
    qDebug()<<stockInfo[3];
    qDebug()<<stockInfo[4];
    qDebug()<<stockInfo[5];
    qDebug()<<stockInfo[0].mid(5,2);
    if(stockInfo[0].mid(5,2) == "hk"){//港股
        this->ui->label_2->setText(tr("港元"));
        this->ui->label_3->setText(tr("港元"));
    }
    else if(stockInfo[0].mid(5,2) == "us"){//美股
        this->ui->label_2->setText(tr("美元"));
        this->ui->label_3->setText(tr("美元"));
    }
    else if(stockInfo[0].mid(5,2) == "sh" || stockInfo[0].mid(5,2) == "sz"){//A股
        this->ui->label_2->setText(tr("元"));
        this->ui->label_3->setText(tr("元"));
    }
    if(stockInfo[4].toDouble() > 0){
        stockInfo[4] = "+" + stockInfo[4];
    }
    if(stockInfo[5].toDouble() > 0){
        stockInfo[5] = "+" + stockInfo[5];
    }
    //涨
    if(stockInfo[4].toDouble() > 0){
        this->ui->labelTitle->setStyleSheet("color:rgb(253,78,80) ; font: 25 14pt \"Microsoft YaHei\";");
        this->ui->labelInfo->setStyleSheet("color:rgb(253,78,80);font: 25 11pt \"Microsoft YaHei\";");
    }
    //跌
    else if(stockInfo[4].toDouble() < 0){
        this->ui->labelTitle->setStyleSheet("color:rgb(30,200,4);font: 25 14pt \"Microsoft YaHei\";");
        this->ui->labelInfo->setStyleSheet("color:rgb(30,200,4);font: 25 11pt \"Microsoft YaHei\";");
    }
    //平
    else{
        this->ui->labelTitle->setStyleSheet("color:rgb(0,0,0);font: 25 14pt \"Microsoft YaHei\";");
        this->ui->labelInfo->setStyleSheet("color:rgb(0,0,0);font: 25 11pt \"Microsoft YaHei\";");
    }
    this->stockCode = stockInfo[1];
    this->ui->labelTitle->setText(stockInfo[1]);
    this->ui->labelInfo->setText(stockInfo[3] + "   " + stockInfo[4] + "   " + stockInfo[5] + "%");
}

StockRemindDialog::~StockRemindDialog()
{
    delete ui;
}

void StockRemindDialog::on_buttonBox_accepted()
{
    if(this->ui->checkBox_1->isChecked()){
        if(this->ui->lineEditRate->text().length() == 0){
            QMessageBox::about(this, tr("提示"), tr("请输入涨跌幅百分比！"));
        }
        else{
            sendData(stockCode , "rate" , this->ui->lineEditRate->text());
        }
    }
    if(this->ui->checkBox_2->isChecked()){
        if(this->ui->lineEditRise->text().length() == 0){
            QMessageBox::about(this, tr("提示"), tr("请输入达到或高于的金额！"));
        }
        else{
            sendData(stockCode , "rise" , this->ui->lineEditRise->text());
        }
    }
    if(this->ui->checkBox_3->isChecked()){
        if(this->ui->lineEditFall->text().length() == 0){
            QMessageBox::about(this, tr("提示"), tr("请输入达到或低于的金额！"));
        }
        else{
            sendData(stockCode , "fall" , this->ui->lineEditFall->text());
        }
    }
}
