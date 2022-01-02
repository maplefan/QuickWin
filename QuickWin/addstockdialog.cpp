#include "addstockdialog.h"
#include "ui_addstockdialog.h"

AddStockDialog::AddStockDialog(QString stockConfig , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStockDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->stockConfig = stockConfig;
}

AddStockDialog::~AddStockDialog()
{
    delete ui;
}

void AddStockDialog::on_buttonBox_accepted()
{
    QString place = this->ui->comboBox->currentText();
    QString stockCode = this->ui->lineEdit->text();
    qDebug()<<"place:"<<place;
    qDebug()<<"stockCode"<<stockCode;
    QString result = "";
    if(place == "港股"){
        qDebug()<<"hk";
        if(stockCode.size() != 5){
            result = "hk";
            emit sendData(result);
            return;
        }
        result = "s_hk" + stockCode;
    }
    else if(place == "美股"){
                qDebug()<<"us";
        result = "s_us" + stockCode;
    }
    else if(place == "A股"){
                qDebug()<<"A";
        //上海交易所的股票代码以600、601、603开头，深圳交易所的股票代码以000、002、003开头，创业板的股票代码以300开头（深圳交易所上市），科创板的股票代码以688开头（上海交易所上市）
        if(stockCode.size() != 6){
            result = "cn";
            emit sendData(result);
             return;
        }
        QString code = stockCode.mid(0,3);
        if(code == "600" || code == "601" || code == "603" || code == "688"){
            //上海证券交易所
            result = "s_sh" + stockCode;
        }
        else if(code == "000" || code == "002" || code == "003" || code == "300"){
            //深圳证券交易所
            result = "s_sz" + stockCode;
        }
        else{
            result = "cn";
            emit sendData(result);
            return;
        }
    }
    qDebug()<<"result"<<result;
    //判重
    if(stockConfig.indexOf(result) != -1){
        result = "repeat";
        emit sendData(result);
        return;
    }
    else{
        emit sendData(result);
        return;
    }
}
