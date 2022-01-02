#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "fileform.h"
#include "ui_fileform.h"

FileForm::FileForm(QString path ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    QFileInfo info(path);
    if(info.isDir()){
        QFileIconProvider provider;
        QIcon icon = provider.icon(path);
        QPixmap pixmap = icon.pixmap(icon.availableSizes().last());
        //QPixmap pixmap = QtWin::fromHICON(GetFileIcon(path.toStdString().c_str()));
        pixmap = pixmap.scaled(128 , 128 , Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->ui->img->setPixmap(pixmap);
        this->ui->size->setVisible(false);
        this->ui->name->setText(info.fileName());
    }
    else{
        this->ui->name->setText(info.fileName());
    }
    double size = info.size();
    if(size < 1024){
        this->ui->size->setText(tr("文件大小：") + QString::number(size)+" B");
    }
    else if(size < 1024*1024){
        size = size /1024;
        this->ui->size->setText(tr("文件大小：") + QString::number(size , 'f' , 2)+" KB");
    }
    else if(size < 1024*1024*1024){
        size = size /(1024*1024);
        this->ui->size->setText(tr("文件大小：") + QString::number(size , 'f' , 2)+" MB");
    }
    else if(size < 1024*1024*1024*1024){
        size = size /(1024*1024*1024);
        this->ui->size->setText(tr("文件大小：") + QString::number(size , 'f' , 2)+" GB");
    }
    else if(size < 1024*1024*1024*1024*1024){
        size = size /(1024*1024*1024*1024);
        this->ui->size->setText(tr("文件大小：") + QString::number(size , 'f' , 2)+" TB");
    }
    QFileIconProvider provider;
    QIcon icon = provider.icon(path);
    QPixmap pixmap = icon.pixmap(icon.availableSizes().last());
    //QPixmap pixmap = QtWin::fromHICON(GetFileIcon(path.toStdString().c_str()));
    pixmap = pixmap.scaled(128 , 128 , Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->ui->img->setPixmap(pixmap);
    QString birthTime = (info.birthTime()).toString("yyyy-MM-dd hh:mm:ss");
    if(birthTime.length() == 0){
        birthTime = tr("未知");
    }

    QString lastReadTime = (info.lastRead()).toString("yyyy-MM-dd hh:mm:ss");
    if(lastReadTime.length() == 0){
        lastReadTime = tr("未知");
    }

    this->ui->createtime->setText(tr("创建日期：")+ birthTime);
    this->ui->lastreadtime->setText(tr("修改日期：") + lastReadTime);

    QFont fontName( "Microsoft YaHei", 15, 50);
    this->ui->name->setFont(fontName);
    QFont fontOthers( "Microsoft YaHei", 10, 25);
    this->ui->size->setFont(fontOthers);
    this->ui->createtime->setFont(fontOthers);
    this->ui->lastreadtime->setFont(fontOthers);
}

FileForm::~FileForm()
{
    delete ui;
}

//获得文件图标
HICON FileForm::GetFileIcon(const char* filePath){
    // get ICON index
    SHFILEINFOA sfi = {0};
    SHGetFileInfoA(filePath , 0 , &sfi , sizeof(sfi),SHGFI_ICON|SHGFI_SYSICONINDEX| SHGFI_USEFILEATTRIBUTES );
    // get image list.
    // To get the 48x48 icons, use SHIL_EXTRALARGE
    // To get the 256x256 icons (Vista only), use SHIL_JUMBO
    IImageList* imageList;

    HRESULT hResult = SHGetImageList(SHIL_JUMBO, IID_IImageList, (void**)&imageList);

    if (hResult == S_OK)
    {
        // Get the icon we need from the list. Note that the HIMAGELIST we retrieved
        // earlier needs to be casted to the IImageList interface before use.
        HICON hIcon;
        hResult = (imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);

        if (hResult == S_OK)
        {
            return hIcon;
        }
    }
    return NULL;
}

//获得文件夹图标
HICON FileForm::GetFolderIcon(const char* filePath){
    // get ICON index
    SHFILEINFOA sfi = {0};
    SHGetFileInfoA(filePath , FILE_ATTRIBUTE_DIRECTORY , &sfi , sizeof(sfi),SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);

    // get image list.
    // To get the 48x48 icons, use SHIL_EXTRALARGE
    // To get the 256x256 icons (Vista only), use SHIL_JUMBO
    IImageList* imageList;

    HRESULT hResult = SHGetImageList(SHIL_JUMBO, IID_IImageList, (void**)&imageList);

    if (hResult == S_OK)
    {
        // Get the icon we need from the list. Note that the HIMAGELIST we retrieved
        // earlier needs to be casted to the IImageList interface before use.
        HICON hIcon;
        hResult = (imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);

        if (hResult == S_OK)
        {
            return hIcon;
        }
    }
    return NULL;
}
