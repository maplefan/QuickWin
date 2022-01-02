#include "musicwindow.h"
#include "ui_musicwindow.h"

MusicWindow::MusicWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
}

MusicWindow::~MusicWindow()
{
    delete ui;
}

void MusicWindow::playUrl(QUrl url){
    this->ui->widget->playUrl(url);
    QStringList s = url.toString().split("/");
    this->setWindowTitle(s[s.size()-1]);

}
