#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QMainWindow>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>
#include <Windows.h>
#include <QScreen>
namespace Ui {
class ImageForm;
}

class ImageForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageForm(QString filename , QString fileSuffix, QWidget *parent = nullptr);
    bool GetGifSize(const char* path, int* width, int* height);
    bool ImageForm::GetPicSize(const char* path, int *punWidth, int *punHeight);
    ~ImageForm();

private:
    Ui::ImageForm *ui;
    QPixmap pix;
    QPoint offset;
    double picScale;
    bool isGif;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // IMAGEFORM_H
