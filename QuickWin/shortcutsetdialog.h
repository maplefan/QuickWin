#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SHORTCUTSETDIALOG_H
#define SHORTCUTSETDIALOG_H

#include <QMainWindow>
#include <QApplication>
#include <QAbstractButton>
#include <QDialog>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include "config.h"
#include "setting.h"
#include "MyGlobalShortcut/MyGlobalShortCut.h"

namespace Ui {
class ShortcutSetDialog;
}

class ShortcutSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShortcutSetDialog(QWidget *parent = nullptr);
    ~ShortcutSetDialog();

    bool eventFilter(QObject *, QEvent *);
    // 初始化
    void init();

signals:
    void initShortcut();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ShortcutSetDialog *ui;
    bool isStockTipNormal;
    bool isHardwareTipNormal;
    bool isMainToolTipNormal;
    bool isReminderTipNormal;
    bool isScreenShotTipNormal;
    bool isStickyNoteTipNormal;
    bool isColorPickerTipNormal;
    bool isTaskManagerTipNormal;
    bool isHotkeyManagerTipNormal;
    bool isSearchTipNormal;
    bool isTranslatorTipNormal;

    /* 提示信息对话框 */
    void showMessage(QString msg);
    /* 保存输入框数据到本地txt文本，并更新快捷键值 */
    bool save();
};

#endif // SHORTCUTSETDIALOG_H
