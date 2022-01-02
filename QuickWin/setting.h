#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SETTING_H
#define SETTING_H

#include <QFileDialog>
#include <QTranslator>
#include <QMainWindow>
#include <QSettings>
#include <QDir>
#include <Windows.h>
#include <QProcess>
#include <QDebug>
#include "config.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QListView>
#include <QStandardItemModel>
#include <shortcutsetdialog.h>

static QTranslator* translator;

namespace Ui {
class Setting;
}

enum LangSetting
{
    LANGCHINESE = 0,
    LANGTRADCHINESE,
    LANGENGLISH
};

enum ShowInfo
{
    UPLOADSPEED = 0,//上传速度
    DOWNLOADSPEED,//下载速度
    CPUUTIL,//CPU使用率
    MEMORYUTIL,//内存使用率
    CPUTEMP,//CPU核心温度
    GPUTEMP,//GPU核心温度
    CPUPOWER,//CPU功率
    GPUPOWER,//GPU功率
    GPUUTIL,//GPU使用率
    HARDDISKTEMP,//硬盘温度
};

int getNofX(int x , int n);
void setNofXto1(int &x , int n);
void setNofXto0(int &x , int n);

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    bool IsWow64();
    void SetProcessAutoRunSelf(const QString &appPath , bool b);
    void SetProcessScreenProtect();

private slots:
    void on_checkBoxAutoStart_stateChanged(int arg1);

    void on_pushButtonSetScreenProtect_clicked();

    void on_pushButtonSetFont_clicked();

    void on_pushButtonSetHotkey_clicked();

    void on_pushButtonMainChooseFont_clicked();

    void on_pushButtonMainChooseColor_clicked();

    void on_pushButtonTaskChooseFont_clicked();

    void on_pushButtonTaskChooseColor_clicked();

    void on_pushButtonMainChooseColorBK_clicked();

    void on_comboBoxMonitor_currentIndexChanged(int index);

public slots:
    void comboBoxLanguage_currentIndexChanged(int index);
    void comboBoxStockShow_currentIndexChanged(int index);
    void checkBox_stateChanged(int arg1);
    void checkBoxHideMainWindow_stateChanged(int arg1);
    void checkBoxQuickLook_stateChanged(int arg1);
    void comboBoxMainDoubleClickAction_currentIndexChanged(int index);
    void comboBoxTaskDoubleClickAction_currentIndexChanged(int index);
    void horizontalSliderMonitorBrightness_valueChanged(int value);
    void horizontalSliderMonitorContrast_valueChanged(int value);
    void checkBoxMainUploadSpeed_stateChanged(int arg1);
    void checkBoxMainDownloadSpeed_stateChanged(int arg1);
    void checkBoxMainCPUUtil_stateChanged(int arg1);
    void checkBoxMainMemoryUtil_stateChanged(int arg1);
    void checkBoxMainMBTemp_stateChanged(int arg1);
    void checkBoxMainMBFan_stateChanged(int arg1);
    void checkBoxMainCPUTemp_stateChanged(int arg1);
    void checkBoxMainGPUTemp_stateChanged(int arg1);
    void checkBoxMainCPUPower_stateChanged(int arg1);
    void checkBoxMainGPUPower_stateChanged(int arg1);
    void checkBoxMainGPUUtil_stateChanged(int arg1);
    void checkBoxMainHardDiskTemp_stateChanged(int arg1);
    void checkBoxTaskUploadSpeed_stateChanged(int arg1);
    void checkBoxTaskDownloadSpeed_stateChanged(int arg1);
    void checkBoxTaskCPUUtil_stateChanged(int arg1);
    void checkBoxTaskMemoryUtil_stateChanged(int arg1);
    void checkBoxTaskMBTemp_stateChanged(int arg1);
    void checkBoxTaskMBFan_stateChanged(int arg1);
    void checkBoxTaskCPUTemp_stateChanged(int arg1);
    void checkBoxTaskGPUTemp_stateChanged(int arg1);
    void checkBoxTaskCPUPower_stateChanged(int arg1);
    void checkBoxTaskGPUPower_stateChanged(int arg1);
    void checkBoxTaskGPUUtil_stateChanged(int arg1);
    void checkBoxTaskHardDiskTemp_stateChanged(int arg1);
    void comboBoxUpdateTime_currentIndexChanged(int index);

private:
    Ui::Setting *ui;
    int currentMonitorIndex;
};

#endif // SETTING_H
