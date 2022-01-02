#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef QUICKLOOK_H
#define QUICKLOOK_H

#include <QScreen>
#include <QMainWindow>
#include <fstream>
#include <memory>
#include <QDesktopWidget>
#include "pdfform.h"
#include "officeform.h"
#include "markdownForm.h"
#include "htmlform.h"
#include "imageform.h"
#include "musicplayer.h"
#include "fileform.h"
#include "textForm.h"
#include "musicwindow.h"

namespace Ui {
class QuickLook;
}

enum FILETYPE{
    PDF = 0,
    OFFICEWORD,
    OFFICEEXCEL,
    MARKDOWN,
    HTML,
    PIC,
    AUDIO,
    VIDEO,
    LNK,
    TXT,
    OTHER,
};

class QuickLook : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuickLook(QWidget *parent = 0);
    explicit QuickLook(QString filePath ,QWidget *parent = 0);
    ~QuickLook();
    QByteArray GetFileContents(const char* filename, size_t *size);
    QUrl encode(const QString& istr);
    FILETYPE GetFileType(const QFileInfo &info);
    void close();
    void destoryThis();

private:
    Ui::QuickLook *ui;
};

#endif // QUICKLOOK_H
