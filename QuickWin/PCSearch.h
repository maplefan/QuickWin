#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef PCSEARCH_H
#define PCSEARCH_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <windows.h>
#include "tlhelp32.h"
#include <string.h>
#include <shellapi.h>
#include <QProcess>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QDateTime>
#include <QToolTip>
#include <QFileIconProvider>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QClipboard>
#include <QLabel>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class PCSearch; }
QT_END_NAMESPACE
class PCSearch : public QMainWindow
{
    Q_OBJECT

public:
    PCSearch(QWidget *parent = nullptr);
    ~PCSearch();
    HWND GetHwndByPid(DWORD dwProcessID);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    DWORD GetProcessidFromName(LPCTSTR name);
    bool IsEnglish(QString &qstrSrc);//判断是否全是英文
    QString changeSizeFmt(qint64 size);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_returnPressed();
    void slotWindowContextMenu(QPoint pos);
    void showToolTip(const QModelIndex &index);
    void viewFile();
    void openFile();
    void openFilePath();
    void copyFullPath();
    void viewProperties();
    void keyPressRowChange(const QModelIndex &, const QModelIndex &);
    bool eventFilter(QObject* object, QEvent* event);

private:
    Ui::PCSearch *ui;
    QPoint m_startPos;
    QStandardItemModel *model;
    int colWidth0, colWidth1 , colWidth2 , colWidth3;
    QFileIconProvider iconProvider;
    QAction *actionView;
    QAction *actionOpen;
    QAction *actionOpenPath;
    QAction *actionCopyFullPath;
    QAction *actionAttribute;
    QMenu *menu;
    QClipboard *clipboard;
    QLabel *statusLabel;
    bool isFileMode;
};
#endif // PCSEARCH_H
