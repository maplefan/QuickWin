#include "imageform.h"
#include "ui_imageform.h"

ImageForm::ImageForm(QString filename , QString fileSuffix, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    picScale = 1;
    isGif = false;
    int picWidth = 0;
    int picHeight = 0;
    if( fileSuffix == "gif" ){//显示gif图片
        isGif = true;
        QMovie *movie = new QMovie(filename);
        if(GetGifSize(filename.toStdString().c_str() , &picWidth , &picHeight)){
            setFixedSize(picWidth , picHeight);
            ui->label->setGeometry( 0 , 0 , picWidth , picHeight);
        }
        ui->label->setMovie(movie);
        movie->start();
    }
    else if( fileSuffix == "jpg" || fileSuffix == "jpeg" ||fileSuffix == "png" || fileSuffix == "bmp" ){//显示静态图片
        isGif = false;
        if(GetPicSize(filename.toStdString().c_str() , &picWidth , &picHeight)){
            //修复像素大于屏幕宽度以及高度的用户体验问题
            //int nWidth = GetSystemMetrics(SM_CXSCREEN);
            //int nHeight = GetSystemMetrics(SM_CYSCREEN);
            QScreen *screen = QGuiApplication::primaryScreen ();
            QRect screenRect =  screen->availableGeometry();
            int nWidth = screenRect.width();
            int nHeight = screenRect.height();
            double dWidth = nWidth;
            double dHeight = nHeight;
            double dPicWidth = picWidth;
            double dPicHeight = picHeight;
            while(dPicWidth > nWidth || dPicHeight > nHeight){
                dPicWidth = dPicWidth/1.5;
                dPicHeight = dPicHeight/1.5;
            }
            picWidth = dPicWidth;
            picHeight = dPicHeight;
        }
        pix =  QPixmap(filename);
        ui->label->setPixmap(pix);
        ui->label->setGeometry(0,0,picWidth , picHeight);
        ui->label->setScaledContents(true);
        qDebug()<<"pic"<<picWidth<<" "<<picHeight;
        setFixedSize(picWidth , picHeight);
    }
}

ImageForm::~ImageForm()
{
    delete ui;
}

bool ImageForm::GetGifSize(const char* file_path, int* width, int* height)//获得gif图片的尺寸
{
    bool has_image_size = false;
    int file_size;
    *height = -1;
    *width = -1;
    file_size = -1;
    FILE * fp = fopen(file_path, "rb");
    if (fp == NULL)
    return has_image_size;
    struct stat st;
    char sigBuf[26];
    if (fstat(fileno(fp), &st) < 0)
    {
    fclose(fp);
    return has_image_size;
    }
    else
    {
    file_size = st.st_size;
    }
    if (fread(&sigBuf, 26, 1, fp) < 1)
    {
    fclose(fp);
    return has_image_size;
    }
    const char* gif87_signature = "GIF87a";
    const char* gif89_signature = "GIF89a";
    if ((file_size >= 10) && (memcmp(sigBuf, gif87_signature, strlen(gif87_signature)) == 0 || memcmp(sigBuf, gif89_signature, strlen(gif89_signature)) == 0))
    {
        // image type: gif
        unsigned short* size_info = (unsigned short*)(sigBuf + 6);
        *width = size_info[0];
        *height = size_info[1];
        has_image_size = true;
    }
    if (fp != NULL)
        fclose(fp);
    return has_image_size;
}

bool ImageForm::GetPicSize(const char* path, int *punWidth, int *punHeight)
{
    QImage img(path);
    if(img.isNull()){
        return false;
    }
    *punWidth = img.width();
    *punHeight = img.height();
    return true;
}

void ImageForm::mousePressEvent(QMouseEvent *event) // 鼠标按下事件
{
    if(event->button() == Qt::LeftButton){       // 如果是鼠标左键按下
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor); // 使鼠标指针暂时改变形状
        offset = event->globalPos() - pos();    // 获取指针位置和窗口位置的差值
    }
    else if(event->button() == Qt::RightButton){ // 如果是鼠标右键按下
        QCursor cursor(QPixmap("../mymouseevent/logo.png"));
        QApplication::setOverrideCursor(cursor);// 使用自定义的图片作为鼠标指针
    }
}

void ImageForm::mouseMoveEvent(QMouseEvent *event) // 鼠标移动事件
{
    if(event->buttons() & Qt::LeftButton){      // 这里必须使用buttons()
        QPoint temp;
        temp = event->globalPos() - offset;
        move(temp);// 使用鼠标指针当前的位置减去差值，就得到了窗口应该移动的位置
    }
}

void ImageForm::mouseReleaseEvent(QMouseEvent *event) // 鼠标释放事件
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();         // 恢复鼠标指针形状
}

void ImageForm::wheelEvent(QWheelEvent *event)    // 滚轮事件
{
    if(!isGif){
        double offsetX = 0;
        double offsetY = 0;
        QPoint pos = event->pos();
        if(event->delta() > 0){                    // 当滚轮远离使用者时
            //ui->textEdit->zoomIn();                // 进行放大
            picScale = picScale *1.2;
            QPixmap pixmap = pix.scaled(picScale*pix.width() , picScale*pix.height() , Qt::KeepAspectRatio);
            offsetX = pos.x()*picScale - pos.x();
            offsetY = pos.y()*picScale - pos.y();

            ui->label->setGeometry( -offsetX , -offsetY , pixmap.width() , pixmap.height());
            this->ui->label->setPixmap(pixmap);
            repaint();

        }else{                                     // 当滚轮向使用者方向旋转时
            //ui->textEdit->zoomOut();               // 进行缩小
            picScale = picScale /1.2;
            QPixmap pixmap = pix.scaled(picScale*pix.width() , picScale*pix.height() , Qt::KeepAspectRatio);
            offsetX = pos.x()*picScale - pos.x();
            offsetY = pos.y()*picScale - pos.y();

            ui->label->setGeometry( -offsetX , -offsetY , pixmap.width() , pixmap.height());
            this->ui->label->setPixmap(pixmap);
            repaint();
        }
    }
}

