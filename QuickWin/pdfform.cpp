#include "pdfform.h"
#include "ui_pdfform.h"
#include <QDebug>

PDFForm::PDFForm(QString filename, QByteArray &bytearray, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PDFForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    FileLength_ = bytearray.length();
    File_ = new char[FileLength_];
    //处理流数据记住，要用memcpy
    //千万别犯傻去用strcpy和qt自带的杂七杂八东西
    memcpy(File_, bytearray.toStdString().c_str(), FileLength_);
    FileName_ = filename.toStdString();
    Picture_ = new PictureBox();
    Picture_->setMode(PictureBox::PB_MODE::FIX_SIZE_CENTRED );
    this->ui->verticalLayout_1->addWidget(Picture_);
    connect(this->ui->verticalScrollBar , SIGNAL(valueChanged(int)) , this , SLOT(scrollChange()));
}

PDFForm::~PDFForm()
{
    HaveLoadPdf_ = false;
    if(Picture_)
    {
        delete Picture_;
        Picture_ = nullptr;
    }
    if(File_)
    {
        delete []File_;
    }
    PDFMANAGER_Closepdf(FileName_.c_str());
    delete ui;
}

void PDFForm::InitFile()
{
    qDebug()<<"QuickLook pdf initfile";
    if(HaveLoadPdf_)
        return;
    int length = (int)FileLength_;
    qDebug()<<"QuickLook pdf initfile1";
    if(PDFMANAGER_Loadpdf(FileName_.c_str(), File_, length)){
        HaveLoadPdf_ = true;
        PageCount_ = PDFMANAGER_GetPageCount(FileName_.c_str());
        this->ui->verticalScrollBar->setMinimum(1);
        this->ui->verticalScrollBar->setMaximum(PageCount_);
        this->ui->verticalScrollBar->setPageStep(1);//设置滚轮步长
        IsLoadSuccess = this->LoadPage(0);
    }
}

//加载页面
bool PDFForm::LoadPage(int page)
{
    if(!HaveLoadPdf_)
        return false;
    int length = 0;
    QRect rect = this->ui->verticalLayout_1->geometry();
    float width = rect.width();
    float height = rect.height();
    qDebug()<<FileName_.c_str();
    char* Buffer = NULL;
    try{
        Buffer = PDFMANAGER_LoadPage(FileName_.c_str(),page, width, height, length, false);
        qDebug()<<"pdf:"<<FileName_.c_str()<<" "<<page<<" "<<width<<" "<<height;
        if(length == 0){
            return false;
        }
    }catch(std::exception& e){
        qWarning() << "exception:" << e.what();
    }
    if(Buffer == NULL){
        return false;
    }
    QImage image((uchar*)Buffer, width, height, QImage::Format_RGBA8888);
    this->Picture_->setImage(image);
    PDFMANAGER_ClosePage(FileName_.c_str(),page);//释放页面内存
    UpdateLabelPage();
    return true;
}

//界面尺寸变化
void PDFForm::resizeEvent(QResizeEvent *event)
{
    //this->ui->verticalLayout_1->setGeometry(this->ui->widget->geometry());
    qDebug()<<"QuickLook pdf resizeEvent";
    InitFile();
    if(IsLoadSuccess){
        IsLoadSuccess = LoadPage(CurrentPage_);
    }
}

//更新页面数据
void PDFForm::UpdateLabelPage()
{
    int pagecount = PDFMANAGER_GetPageCount(FileName_.c_str());
    int currentpage = PDFMANAGER_GetCurrentPage(FileName_.c_str());
    CurrentPage_ = currentpage-1;
    QString pagelabel = QString("%1/%2" + tr("页")).arg(currentpage).arg(pagecount);
    setWindowTitle(pagelabel + " " + QString::fromStdString(FileName_));
    //this->ui->label_PageNum->setText(pagelabel);
}

void PDFForm::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
    return;
}

//鼠标滚轮事件
void PDFForm::wheelEvent(QWheelEvent *event)
{

    if(event->delta() > 0)// 当滚轮向上滚时
    {
        if(CurrentPage_ <= 0){
            CurrentPage_ = 1;
        }
        else{
            CurrentPage_--;
            this->ui->verticalScrollBar->setValue(CurrentPage_+1);
        }
    }
    else//当滚轮向下滚时
    {
        if(CurrentPage_ >= PageCount_-1){
            CurrentPage_ = PageCount_-1;
        }
        else{
            CurrentPage_++;
            this->ui->verticalScrollBar->setValue(CurrentPage_+1);
        }
    }
}

void PDFForm::scrollChange()//滚轮的值改变的时候
{
    if(IsLoadSuccess){
        IsLoadSuccess = LoadPage(this->ui->verticalScrollBar->value()-1);
    }
}
