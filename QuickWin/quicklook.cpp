#include "quicklook.h"
#include "ui_quicklook.h"
#include <QFileInfo>
#include <VideoForm.h>

QUrl QuickLook::encode(const QString& istr)
{
   QByteArray data;
   data.append(istr);
   return QUrl::fromEncoded(data);
}

//打开pdf文件，C++函数，需要以二进制格式打开
QByteArray QuickLook::GetFileContents(const char* filename, size_t *size)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()){
        std::printf("open file Failed!\n");
        std::printf("%s\n", filename);
        file.close();
        return nullptr;
    }
    *size = file.size();
    QByteArray array;
    array =  file.read(*size);
    return array;
}

QuickLook::QuickLook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuickLook)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
}

QuickLook::QuickLook(QString filePath , QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuickLook)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    //this->setAttribute(Qt::WA_DeleteOnClose);
    QFileInfo file(filePath);
    qDebug()<<"QuickLook:"<<filePath;
    if(file.isDir()){//文件夹
         FileForm *ff = new FileForm(file.absoluteFilePath() , parent);
         ff->setWindowTitle(file.fileName());
         ff->show();
         QScreen *screen = QGuiApplication::primaryScreen ();
         QRect m_screenRect = screen->availableVirtualGeometry();
         if(ff->y() <= m_screenRect.y()){
             ff->move( ff->x() , m_screenRect.y());
         }
    }
    else{//文件
        QString fileSuffix = file.suffix();
        switch (GetFileType(file)) {
            case PDF:
            {//pdf文件
                QString filename = filePath;
                size_t file_length = 0;
                //用智能指针是不想管理打开的文件
                qDebug()<<"QuickLook:"<<filename.toStdString().c_str();
                //std::unique_ptr<char> FileDat_ = std::move(std::unique_ptr<char> (GetFileContents(filename.toStdString().c_str(), &file_length)));
                QByteArray bytearray = GetFileContents(filename.toStdString().c_str(), &file_length);
                qDebug()<<"QuickLook length:"<<file_length;
                PDFForm *form = new PDFForm(filename, bytearray , parent);
                form->setWindowTitle(filename);
                form->showNormal();
                qDebug()<<"QuickLook shownormal";
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(form->y() <= m_screenRect.y()){
                    form->move( form->x() , m_screenRect.y());
                }
                //必须先show再初始化
                form->InitFile();
                break;
            }
            case MARKDOWN:
            {//markdown文件
                QString filename = filePath;
                MarkdownForm *md = new MarkdownForm(filename , parent);
                md->setWindowTitle(file.fileName());
                md->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(md->y() <= m_screenRect.y()){
                    md->move( md->x() , m_screenRect.y());
                }
                break;
            }
            case HTML:
            {//html文件
                QString filename = filePath;
                HtmlForm *form = new HtmlForm(filename , parent);
                form->setWindowTitle(file.fileName());
                form->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(form->y() <= m_screenRect.y()){
                    form->move( form->x() , m_screenRect.y());
                }
                break;
            }
            case PIC:
            {//图片文件
                QString filename = filePath;
                ImageForm *form = new ImageForm(filename ,fileSuffix, parent );
                form->setWindowTitle(file.fileName());
                form->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(form->y() <= m_screenRect.y()){
                    form->move( form->x() , m_screenRect.y());
                }
                break;
            }
            case AUDIO:
            {//音频文件
                QString filename = filePath;
                MusicWindow *mw = new MusicWindow(parent);
                mw->setWindowTitle(file.fileName());
                mw->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(mw->y() <= m_screenRect.y()){
                    mw->move( mw->x() , m_screenRect.y());
                }
                mw->playUrl(QUrl::fromLocalFile(filename));
                break;
            }
            case VIDEO:
            {//视频文件
                QString filename = filePath;
                VideoForm *vf = new VideoForm(filename);
                vf->setAttribute(Qt::WA_DeleteOnClose,  true);
                vf->setWindowTitle(file.fileName());
                vf->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(vf->y() <= m_screenRect.y()){
                    vf->move( vf->x() , m_screenRect.y());
                }
                break;
            }
            case TXT:
            {
                TextForm *tf = new TextForm(parent);
                tf->openFile(filePath);
                tf->setWindowTitle(file.fileName());
                tf->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(tf->y() <= m_screenRect.y()){
                    tf->move( tf->x() , m_screenRect.y());
                }
                break;
            }
            case LNK:
            {//快捷方式文件
                FileForm *ff = new FileForm(file.symLinkTarget() , parent);
                ff->setWindowTitle(file.fileName());
                ff->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(ff->y() <= m_screenRect.y()){
                    ff->move( ff->x() , m_screenRect.y());
                }
                break;
            }
        case OFFICEWORD:
        //暂时未启用word
        /*{//word文件
            QString filename = filePath;
            OfficeForm *form = new OfficeForm();
            form->OpenWord(filename);
            form->setWindowTitle(file.fileName());
            form->show();
            QScreen *screen = QGuiApplication::primaryScreen ();
            QRect m_screenRect = screen->availableVirtualGeometry();
            if(form->y() <= m_screenRect.y()){
                form->move( form->x() , m_screenRect.y());
            }
            break;
        }*/
        case OFFICEEXCEL:
        //暂时未启用excel
        /*{//excel文件
            QString filename = filePath;
            OfficeForm *form = new OfficeForm();
            form->OpenExcel(filename);
            form->setWindowTitle(file.fileName());
            form->show();
            QScreen *screen = QGuiApplication::primaryScreen ();
            QRect m_screenRect = screen->availableVirtualGeometry();
            if(form->y() <= m_screenRect.y()){
                form->move( form->x() , m_screenRect.y());
            }
            break;
        }*/
        case OTHER:
            {//其他类型文件
                FileForm *ff = new FileForm(file.absoluteFilePath() , parent);
                ff->setWindowTitle(file.fileName());
                ff->show();
                QScreen *screen = QGuiApplication::primaryScreen ();
                QRect m_screenRect = screen->availableVirtualGeometry();
                if(ff->y() <= m_screenRect.y()){
                    ff->move( ff->x() , m_screenRect.y());
                }
                break;
            }
        }
    }
}

QuickLook::~QuickLook()
{
    this->destroy();
    delete ui;
}

FILETYPE QuickLook::GetFileType(const QFileInfo &file){
    QString fileSuffix = file.suffix();//获得文件拓展名
    if(fileSuffix == "pdf"){//pdf文件
        return PDF;
    }
    else if(fileSuffix == "doc" || fileSuffix == "docx"){//word文件
        return OFFICEWORD;
    }
    else if(fileSuffix == "xls" || fileSuffix == "xlsx"){//excel文件
       return OFFICEEXCEL;
    }
    else if(fileSuffix == "md" || fileSuffix == "markdown"){//markdown文件
        return MARKDOWN;
    }
    else if(fileSuffix == "html" || fileSuffix == "htm"){//html文件
        return HTML;
    }
    else if(fileSuffix == "png" || fileSuffix == "jpg" || fileSuffix == "jpeg" || fileSuffix == "bmp" || fileSuffix == "gif"){//图片文件
        return PIC;
    }
    else if(fileSuffix == "mp3" || fileSuffix == "wma"){//音频文件
        return AUDIO;
    }
    else if(fileSuffix == "mp4" || fileSuffix == "mkv"){//视频文件
       return VIDEO;
    }
    else if(fileSuffix == "txt" ||
            fileSuffix == "c" ||
            fileSuffix == "cpp" ||
            fileSuffix == "hpp" ||
            fileSuffix == "h" ||
            fileSuffix == "java" ||
            fileSuffix == "cs" ||
            fileSuffix == "py" ||
            fileSuffix == "js" ||
            fileSuffix == "css" ||
            fileSuffix == "xml")
    {
        return TXT;
    }
    else if(fileSuffix == "lnk"){//快捷方式文件
        if(file.exists() && file.isSymLink()){//快捷方式文件存在且指向一个地址
            return LNK;
        }
        else{
            return OTHER;
        }
    }
    else{//其他类型文件
        return OTHER;
    }
}

void QuickLook::close(){
    this->destroy();
    this->close();
}

void QuickLook::destoryThis(){
    this->destroy();
}
