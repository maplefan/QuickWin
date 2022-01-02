#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef FILEFORM_H
#define FILEFORM_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QFileIconProvider>
#include <Windows.h>
#include <shellapi.h>
#include <CommCtrl.h>
#include <commoncontrols.h>
#include <QtWin>
namespace Ui {
class FileForm;
}

class FileForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileForm(QString path , QWidget *parent = nullptr);
    ~FileForm();
    HICON GetFileIcon(const char* filePath);
    HICON GetFolderIcon(const char* filePath);

private:
    Ui::FileForm *ui;
};

#endif // FILEFORM_H
