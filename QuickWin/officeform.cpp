#include "officeform.h"
#include "ui_officeform.h"
#include <QtMsgHandler>
#include <QTimer>
#include<ole2.h>

OfficeForm::OfficeForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OfficeForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
}

OfficeForm::~OfficeForm()
{
    this->CloseOffice();
    delete ui;
}

void OfficeForm::OpenExcel(QString filename)
{
    //在函数中添加代码
    HRESULT r = OleInitialize(0);
    if(r!=S_OK && r != S_FALSE)
    {
        return;
    }
    this->CloseOffice();
    officeContent_ = new QAxWidget("Excel.Application", this->ui->widget);
    officeContent_->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    officeContent_->setProperty("DisplayAlerts", false);
    auto rect = this->ui->widget->geometry();
    rect.setLeft(0);
    rect.setTop(0);
    rect.setWidth(1000);
    rect.setHeight(600);
    this->setBaseSize(1000 , 600);
    officeContent_-> setGeometry(rect);
    officeContent_->setControl(filename);
    officeContent_->show();
}

void OfficeForm::OpenWord(QString filename)
{
    //在函数中添加代码
    /*HRESULT r = OleInitialize(0);
    if(r!=S_OK && r != S_FALSE)
    {
        return;
    }*/
    this->CloseOffice();
    officeContent_ = new QAxWidget("Word.Application", this->ui->widget);
    //officeContent_->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    //officeContent_->setProperty("DisplayAlerts", false);
    auto rect = this->ui->widget->geometry();
    rect.setLeft(0);
    rect.setTop(0);
    rect.setWidth(1000);
    rect.setHeight(600);
    this->setBaseSize(1000 , 600);
    officeContent_-> setGeometry(rect);
    officeContent_->setControl(filename);
    officeContent_->show();
    //this->ui->gridLayout->addWidget(officeContent_);
}

void OfficeForm::CloseOffice()
{
    if(this->officeContent_)
    {
        officeContent_->close();
        officeContent_->clear();
        delete officeContent_;
        officeContent_ = nullptr;
    }
}


void OfficeForm::closeEvent(QCloseEvent *event){
    this->CloseOffice();
}
