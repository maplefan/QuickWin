#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QMainWindow>
#include "musicplayer.h"
namespace Ui {
class MusicWindow;
}

class MusicWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MusicWindow(QWidget *parent = nullptr);
    ~MusicWindow();
    void playUrl(QUrl url);

private:
    Ui::MusicWindow *ui;
};

#endif // MUSICWINDOW_H
