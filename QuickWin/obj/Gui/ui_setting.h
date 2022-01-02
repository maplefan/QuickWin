/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QCheckBox *checkBoxAutoStart;
    QComboBox *comboBoxLanguage;
    QLabel *labelLanguage;
    QComboBox *comboBoxStockShow;
    QLabel *labelStockShow;
    QLabel *labelFont;
    QPushButton *pushButtonSetFont;
    QLabel *labelHotkey;
    QPushButton *pushButtonSetHotkey;
    QPushButton *pushButtonSetScreenProtect;
    QLabel *label;
    QLabel *labelFontResult;
    QCheckBox *checkBoxFontWeight;
    QCheckBox *checkBoxQuickLook;
    QGroupBox *groupBox;
    QLabel *labelMonitor;
    QComboBox *comboBoxMonitor;
    QLabel *labelMonitorBrightness;
    QSlider *horizontalSliderMonitorBrightness;
    QLabel *labelMonitorContrast;
    QSlider *horizontalSliderMonitorContrast;
    QLabel *labelMonitorBrightnessValue;
    QLabel *labelMonitorContrastValue;
    QLabel *label_4;
    QComboBox *comboBoxUpdateTime;
    QWidget *tabMainWindow;
    QGroupBox *groupBoxMainFontAndColor;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButtonMainChooseFont;
    QPushButton *pushButtonMainChooseColor;
    QLabel *labelMainFont;
    QLabel *labelMainColor;
    QLabel *label_9;
    QPushButton *pushButtonMainChooseColorBK;
    QLabel *labelMainColorBK;
    QGroupBox *groupBoxMainShowContent;
    QGroupBox *groupBoxTaskShowContent_2;
    QCheckBox *checkBoxMainCPUUtil;
    QCheckBox *checkBoxMainMemoryUtil;
    QCheckBox *checkBoxMainUploadSpeed;
    QCheckBox *checkBoxMainDownloadSpeed;
    QCheckBox *checkBoxMainCPUTemp;
    QCheckBox *checkBoxMainCPUPower;
    QCheckBox *checkBoxMainGPUTemp;
    QCheckBox *checkBoxMainGPUPower;
    QCheckBox *checkBoxMainGPUUtil;
    QCheckBox *checkBoxMainMBTemp;
    QCheckBox *checkBoxMainMBFan;
    QCheckBox *checkBoxMainHardDiskTemp;
    QGroupBox *groupBoxMainOther;
    QLabel *label_7;
    QCheckBox *checkBoxHideMainWindow;
    QComboBox *comboBoxMainDoubleClickAction;
    QLabel *label_2;
    QLabel *labelMainDoubleClickPath;
    QWidget *tabTaskBar;
    QGroupBox *groupBoxTaskOther;
    QLabel *label_12;
    QComboBox *comboBoxTaskDoubleClickAction;
    QLabel *label_3;
    QLabel *labelTaskDoubleClickPath;
    QGroupBox *groupBoxTaskFontAndColor;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButtonTaskChooseFont;
    QPushButton *pushButtonTaskChooseColor;
    QLabel *labelTaskFont;
    QLabel *labelTaskColor;
    QGroupBox *groupBoxTaskShowInfo;
    QGroupBox *groupBoxTaskShowContent;
    QCheckBox *checkBoxTaskCPUUtil;
    QCheckBox *checkBoxTaskMemoryUtil;
    QCheckBox *checkBoxTaskUploadSpeed;
    QCheckBox *checkBoxTaskDownloadSpeed;
    QCheckBox *checkBoxTaskCPUTemp;
    QCheckBox *checkBoxTaskCPUPower;
    QCheckBox *checkBoxTaskGPUTemp;
    QCheckBox *checkBoxTaskGPUPower;
    QCheckBox *checkBoxTaskGPUUtil;
    QCheckBox *checkBoxTaskMBTemp;
    QCheckBox *checkBoxTaskMBFan;
    QCheckBox *checkBoxTaskHardDiskTemp;

    void setupUi(QMainWindow *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->resize(450, 460);
        Setting->setMaximumSize(QSize(450, 460));
        centralwidget = new QWidget(Setting);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        checkBoxAutoStart = new QCheckBox(tabGeneral);
        checkBoxAutoStart->setObjectName(QString::fromUtf8("checkBoxAutoStart"));
        checkBoxAutoStart->setGeometry(QRect(10, 10, 150, 25));
        comboBoxLanguage = new QComboBox(tabGeneral);
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->setObjectName(QString::fromUtf8("comboBoxLanguage"));
        comboBoxLanguage->setGeometry(QRect(200, 40, 150, 25));
        labelLanguage = new QLabel(tabGeneral);
        labelLanguage->setObjectName(QString::fromUtf8("labelLanguage"));
        labelLanguage->setGeometry(QRect(10, 40, 150, 25));
        comboBoxStockShow = new QComboBox(tabGeneral);
        comboBoxStockShow->addItem(QString());
        comboBoxStockShow->addItem(QString());
        comboBoxStockShow->setObjectName(QString::fromUtf8("comboBoxStockShow"));
        comboBoxStockShow->setGeometry(QRect(200, 70, 150, 25));
        labelStockShow = new QLabel(tabGeneral);
        labelStockShow->setObjectName(QString::fromUtf8("labelStockShow"));
        labelStockShow->setGeometry(QRect(10, 70, 150, 25));
        labelFont = new QLabel(tabGeneral);
        labelFont->setObjectName(QString::fromUtf8("labelFont"));
        labelFont->setGeometry(QRect(10, 100, 150, 25));
        pushButtonSetFont = new QPushButton(tabGeneral);
        pushButtonSetFont->setObjectName(QString::fromUtf8("pushButtonSetFont"));
        pushButtonSetFont->setGeometry(QRect(200, 100, 150, 25));
        labelHotkey = new QLabel(tabGeneral);
        labelHotkey->setObjectName(QString::fromUtf8("labelHotkey"));
        labelHotkey->setGeometry(QRect(10, 160, 150, 25));
        pushButtonSetHotkey = new QPushButton(tabGeneral);
        pushButtonSetHotkey->setObjectName(QString::fromUtf8("pushButtonSetHotkey"));
        pushButtonSetHotkey->setGeometry(QRect(200, 160, 150, 25));
        pushButtonSetScreenProtect = new QPushButton(tabGeneral);
        pushButtonSetScreenProtect->setObjectName(QString::fromUtf8("pushButtonSetScreenProtect"));
        pushButtonSetScreenProtect->setGeometry(QRect(290, 10, 120, 25));
        label = new QLabel(tabGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 340, 385, 60));
        label->setWordWrap(true);
        labelFontResult = new QLabel(tabGeneral);
        labelFontResult->setObjectName(QString::fromUtf8("labelFontResult"));
        labelFontResult->setGeometry(QRect(10, 130, 250, 25));
        checkBoxFontWeight = new QCheckBox(tabGeneral);
        checkBoxFontWeight->setObjectName(QString::fromUtf8("checkBoxFontWeight"));
        checkBoxFontWeight->setGeometry(QRect(280, 130, 71, 25));
        checkBoxQuickLook = new QCheckBox(tabGeneral);
        checkBoxQuickLook->setObjectName(QString::fromUtf8("checkBoxQuickLook"));
        checkBoxQuickLook->setGeometry(QRect(165, 10, 120, 25));
        groupBox = new QGroupBox(tabGeneral);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 230, 400, 110));
        labelMonitor = new QLabel(groupBox);
        labelMonitor->setObjectName(QString::fromUtf8("labelMonitor"));
        labelMonitor->setGeometry(QRect(30, 15, 150, 25));
        comboBoxMonitor = new QComboBox(groupBox);
        comboBoxMonitor->setObjectName(QString::fromUtf8("comboBoxMonitor"));
        comboBoxMonitor->setGeometry(QRect(210, 15, 150, 25));
        labelMonitorBrightness = new QLabel(groupBox);
        labelMonitorBrightness->setObjectName(QString::fromUtf8("labelMonitorBrightness"));
        labelMonitorBrightness->setGeometry(QRect(30, 45, 150, 25));
        horizontalSliderMonitorBrightness = new QSlider(groupBox);
        horizontalSliderMonitorBrightness->setObjectName(QString::fromUtf8("horizontalSliderMonitorBrightness"));
        horizontalSliderMonitorBrightness->setGeometry(QRect(190, 45, 150, 25));
        horizontalSliderMonitorBrightness->setOrientation(Qt::Horizontal);
        labelMonitorContrast = new QLabel(groupBox);
        labelMonitorContrast->setObjectName(QString::fromUtf8("labelMonitorContrast"));
        labelMonitorContrast->setGeometry(QRect(30, 75, 150, 25));
        horizontalSliderMonitorContrast = new QSlider(groupBox);
        horizontalSliderMonitorContrast->setObjectName(QString::fromUtf8("horizontalSliderMonitorContrast"));
        horizontalSliderMonitorContrast->setGeometry(QRect(190, 75, 150, 25));
        horizontalSliderMonitorContrast->setOrientation(Qt::Horizontal);
        labelMonitorBrightnessValue = new QLabel(groupBox);
        labelMonitorBrightnessValue->setObjectName(QString::fromUtf8("labelMonitorBrightnessValue"));
        labelMonitorBrightnessValue->setGeometry(QRect(350, 45, 50, 25));
        labelMonitorContrastValue = new QLabel(groupBox);
        labelMonitorContrastValue->setObjectName(QString::fromUtf8("labelMonitorContrastValue"));
        labelMonitorContrastValue->setGeometry(QRect(350, 75, 50, 25));
        label_4 = new QLabel(tabGeneral);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 190, 171, 25));
        comboBoxUpdateTime = new QComboBox(tabGeneral);
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->addItem(QString());
        comboBoxUpdateTime->setObjectName(QString::fromUtf8("comboBoxUpdateTime"));
        comboBoxUpdateTime->setGeometry(QRect(200, 190, 150, 22));
        tabWidget->addTab(tabGeneral, QString());
        tabMainWindow = new QWidget();
        tabMainWindow->setObjectName(QString::fromUtf8("tabMainWindow"));
        groupBoxMainFontAndColor = new QGroupBox(tabMainWindow);
        groupBoxMainFontAndColor->setObjectName(QString::fromUtf8("groupBoxMainFontAndColor"));
        groupBoxMainFontAndColor->setGeometry(QRect(9, 9, 410, 110));
        label_5 = new QLabel(groupBoxMainFontAndColor);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 101, 25));
        label_6 = new QLabel(groupBoxMainFontAndColor);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 50, 100, 25));
        pushButtonMainChooseFont = new QPushButton(groupBoxMainFontAndColor);
        pushButtonMainChooseFont->setObjectName(QString::fromUtf8("pushButtonMainChooseFont"));
        pushButtonMainChooseFont->setGeometry(QRect(260, 20, 125, 25));
        pushButtonMainChooseColor = new QPushButton(groupBoxMainFontAndColor);
        pushButtonMainChooseColor->setObjectName(QString::fromUtf8("pushButtonMainChooseColor"));
        pushButtonMainChooseColor->setGeometry(QRect(260, 50, 125, 25));
        labelMainFont = new QLabel(groupBoxMainFontAndColor);
        labelMainFont->setObjectName(QString::fromUtf8("labelMainFont"));
        labelMainFont->setGeometry(QRect(120, 20, 125, 25));
        labelMainColor = new QLabel(groupBoxMainFontAndColor);
        labelMainColor->setObjectName(QString::fromUtf8("labelMainColor"));
        labelMainColor->setGeometry(QRect(164, 50, 81, 25));
        label_9 = new QLabel(groupBoxMainFontAndColor);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 80, 100, 25));
        pushButtonMainChooseColorBK = new QPushButton(groupBoxMainFontAndColor);
        pushButtonMainChooseColorBK->setObjectName(QString::fromUtf8("pushButtonMainChooseColorBK"));
        pushButtonMainChooseColorBK->setGeometry(QRect(260, 80, 125, 25));
        labelMainColorBK = new QLabel(groupBoxMainFontAndColor);
        labelMainColorBK->setObjectName(QString::fromUtf8("labelMainColorBK"));
        labelMainColorBK->setGeometry(QRect(164, 80, 81, 25));
        groupBoxMainShowContent = new QGroupBox(tabMainWindow);
        groupBoxMainShowContent->setObjectName(QString::fromUtf8("groupBoxMainShowContent"));
        groupBoxMainShowContent->setGeometry(QRect(9, 130, 410, 170));
        groupBoxTaskShowContent_2 = new QGroupBox(groupBoxMainShowContent);
        groupBoxTaskShowContent_2->setObjectName(QString::fromUtf8("groupBoxTaskShowContent_2"));
        groupBoxTaskShowContent_2->setGeometry(QRect(9, 15, 395, 145));
        checkBoxMainCPUUtil = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainCPUUtil->setObjectName(QString::fromUtf8("checkBoxMainCPUUtil"));
        checkBoxMainCPUUtil->setGeometry(QRect(20, 40, 180, 20));
        checkBoxMainMemoryUtil = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainMemoryUtil->setObjectName(QString::fromUtf8("checkBoxMainMemoryUtil"));
        checkBoxMainMemoryUtil->setGeometry(QRect(210, 40, 180, 20));
        checkBoxMainUploadSpeed = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainUploadSpeed->setObjectName(QString::fromUtf8("checkBoxMainUploadSpeed"));
        checkBoxMainUploadSpeed->setGeometry(QRect(20, 20, 180, 20));
        checkBoxMainDownloadSpeed = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainDownloadSpeed->setObjectName(QString::fromUtf8("checkBoxMainDownloadSpeed"));
        checkBoxMainDownloadSpeed->setGeometry(QRect(210, 20, 180, 20));
        checkBoxMainCPUTemp = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainCPUTemp->setObjectName(QString::fromUtf8("checkBoxMainCPUTemp"));
        checkBoxMainCPUTemp->setGeometry(QRect(20, 80, 180, 20));
        checkBoxMainCPUPower = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainCPUPower->setObjectName(QString::fromUtf8("checkBoxMainCPUPower"));
        checkBoxMainCPUPower->setGeometry(QRect(20, 100, 180, 20));
        checkBoxMainGPUTemp = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainGPUTemp->setObjectName(QString::fromUtf8("checkBoxMainGPUTemp"));
        checkBoxMainGPUTemp->setGeometry(QRect(210, 80, 180, 20));
        checkBoxMainGPUPower = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainGPUPower->setObjectName(QString::fromUtf8("checkBoxMainGPUPower"));
        checkBoxMainGPUPower->setGeometry(QRect(210, 100, 180, 20));
        checkBoxMainGPUUtil = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainGPUUtil->setObjectName(QString::fromUtf8("checkBoxMainGPUUtil"));
        checkBoxMainGPUUtil->setGeometry(QRect(20, 120, 180, 20));
        checkBoxMainMBTemp = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainMBTemp->setObjectName(QString::fromUtf8("checkBoxMainMBTemp"));
        checkBoxMainMBTemp->setGeometry(QRect(20, 60, 180, 20));
        checkBoxMainMBFan = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainMBFan->setObjectName(QString::fromUtf8("checkBoxMainMBFan"));
        checkBoxMainMBFan->setGeometry(QRect(210, 60, 180, 20));
        checkBoxMainHardDiskTemp = new QCheckBox(groupBoxTaskShowContent_2);
        checkBoxMainHardDiskTemp->setObjectName(QString::fromUtf8("checkBoxMainHardDiskTemp"));
        checkBoxMainHardDiskTemp->setGeometry(QRect(210, 120, 180, 20));
        groupBoxMainOther = new QGroupBox(tabMainWindow);
        groupBoxMainOther->setObjectName(QString::fromUtf8("groupBoxMainOther"));
        groupBoxMainOther->setGeometry(QRect(9, 310, 410, 105));
        label_7 = new QLabel(groupBoxMainOther);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 45, 150, 25));
        checkBoxHideMainWindow = new QCheckBox(groupBoxMainOther);
        checkBoxHideMainWindow->setObjectName(QString::fromUtf8("checkBoxHideMainWindow"));
        checkBoxHideMainWindow->setGeometry(QRect(20, 15, 330, 25));
        comboBoxMainDoubleClickAction = new QComboBox(groupBoxMainOther);
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->addItem(QString());
        comboBoxMainDoubleClickAction->setObjectName(QString::fromUtf8("comboBoxMainDoubleClickAction"));
        comboBoxMainDoubleClickAction->setGeometry(QRect(200, 45, 160, 25));
        label_2 = new QLabel(groupBoxMainOther);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 75, 150, 25));
        labelMainDoubleClickPath = new QLabel(groupBoxMainOther);
        labelMainDoubleClickPath->setObjectName(QString::fromUtf8("labelMainDoubleClickPath"));
        labelMainDoubleClickPath->setGeometry(QRect(180, 75, 220, 25));
        tabWidget->addTab(tabMainWindow, QString());
        tabTaskBar = new QWidget();
        tabTaskBar->setObjectName(QString::fromUtf8("tabTaskBar"));
        groupBoxTaskOther = new QGroupBox(tabTaskBar);
        groupBoxTaskOther->setObjectName(QString::fromUtf8("groupBoxTaskOther"));
        groupBoxTaskOther->setGeometry(QRect(10, 280, 410, 81));
        label_12 = new QLabel(groupBoxTaskOther);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 15, 150, 25));
        comboBoxTaskDoubleClickAction = new QComboBox(groupBoxTaskOther);
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->addItem(QString());
        comboBoxTaskDoubleClickAction->setObjectName(QString::fromUtf8("comboBoxTaskDoubleClickAction"));
        comboBoxTaskDoubleClickAction->setGeometry(QRect(200, 15, 160, 25));
        label_3 = new QLabel(groupBoxTaskOther);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 45, 150, 25));
        labelTaskDoubleClickPath = new QLabel(groupBoxTaskOther);
        labelTaskDoubleClickPath->setObjectName(QString::fromUtf8("labelTaskDoubleClickPath"));
        labelTaskDoubleClickPath->setGeometry(QRect(180, 45, 220, 25));
        labelTaskDoubleClickPath->setMaximumSize(QSize(16777215, 16777215));
        groupBoxTaskFontAndColor = new QGroupBox(tabTaskBar);
        groupBoxTaskFontAndColor->setObjectName(QString::fromUtf8("groupBoxTaskFontAndColor"));
        groupBoxTaskFontAndColor->setGeometry(QRect(9, 9, 410, 81));
        label_13 = new QLabel(groupBoxTaskFontAndColor);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 20, 100, 25));
        label_14 = new QLabel(groupBoxTaskFontAndColor);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 50, 100, 25));
        pushButtonTaskChooseFont = new QPushButton(groupBoxTaskFontAndColor);
        pushButtonTaskChooseFont->setObjectName(QString::fromUtf8("pushButtonTaskChooseFont"));
        pushButtonTaskChooseFont->setGeometry(QRect(260, 20, 125, 25));
        pushButtonTaskChooseColor = new QPushButton(groupBoxTaskFontAndColor);
        pushButtonTaskChooseColor->setObjectName(QString::fromUtf8("pushButtonTaskChooseColor"));
        pushButtonTaskChooseColor->setGeometry(QRect(260, 50, 125, 25));
        labelTaskFont = new QLabel(groupBoxTaskFontAndColor);
        labelTaskFont->setObjectName(QString::fromUtf8("labelTaskFont"));
        labelTaskFont->setGeometry(QRect(120, 20, 125, 25));
        labelTaskColor = new QLabel(groupBoxTaskFontAndColor);
        labelTaskColor->setObjectName(QString::fromUtf8("labelTaskColor"));
        labelTaskColor->setGeometry(QRect(164, 50, 81, 25));
        groupBoxTaskShowInfo = new QGroupBox(tabTaskBar);
        groupBoxTaskShowInfo->setObjectName(QString::fromUtf8("groupBoxTaskShowInfo"));
        groupBoxTaskShowInfo->setGeometry(QRect(9, 100, 410, 170));
        groupBoxTaskShowContent = new QGroupBox(groupBoxTaskShowInfo);
        groupBoxTaskShowContent->setObjectName(QString::fromUtf8("groupBoxTaskShowContent"));
        groupBoxTaskShowContent->setGeometry(QRect(9, 15, 395, 145));
        checkBoxTaskCPUUtil = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskCPUUtil->setObjectName(QString::fromUtf8("checkBoxTaskCPUUtil"));
        checkBoxTaskCPUUtil->setGeometry(QRect(20, 40, 180, 20));
        checkBoxTaskMemoryUtil = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskMemoryUtil->setObjectName(QString::fromUtf8("checkBoxTaskMemoryUtil"));
        checkBoxTaskMemoryUtil->setGeometry(QRect(210, 40, 180, 20));
        checkBoxTaskUploadSpeed = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskUploadSpeed->setObjectName(QString::fromUtf8("checkBoxTaskUploadSpeed"));
        checkBoxTaskUploadSpeed->setGeometry(QRect(20, 20, 180, 20));
        checkBoxTaskDownloadSpeed = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskDownloadSpeed->setObjectName(QString::fromUtf8("checkBoxTaskDownloadSpeed"));
        checkBoxTaskDownloadSpeed->setGeometry(QRect(210, 20, 180, 20));
        checkBoxTaskCPUTemp = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskCPUTemp->setObjectName(QString::fromUtf8("checkBoxTaskCPUTemp"));
        checkBoxTaskCPUTemp->setGeometry(QRect(20, 80, 180, 20));
        checkBoxTaskCPUPower = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskCPUPower->setObjectName(QString::fromUtf8("checkBoxTaskCPUPower"));
        checkBoxTaskCPUPower->setGeometry(QRect(20, 100, 180, 20));
        checkBoxTaskGPUTemp = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskGPUTemp->setObjectName(QString::fromUtf8("checkBoxTaskGPUTemp"));
        checkBoxTaskGPUTemp->setGeometry(QRect(210, 80, 180, 20));
        checkBoxTaskGPUPower = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskGPUPower->setObjectName(QString::fromUtf8("checkBoxTaskGPUPower"));
        checkBoxTaskGPUPower->setGeometry(QRect(210, 100, 180, 20));
        checkBoxTaskGPUUtil = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskGPUUtil->setObjectName(QString::fromUtf8("checkBoxTaskGPUUtil"));
        checkBoxTaskGPUUtil->setGeometry(QRect(20, 120, 180, 20));
        checkBoxTaskMBTemp = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskMBTemp->setObjectName(QString::fromUtf8("checkBoxTaskMBTemp"));
        checkBoxTaskMBTemp->setGeometry(QRect(20, 60, 180, 20));
        checkBoxTaskMBFan = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskMBFan->setObjectName(QString::fromUtf8("checkBoxTaskMBFan"));
        checkBoxTaskMBFan->setGeometry(QRect(210, 60, 180, 20));
        checkBoxTaskHardDiskTemp = new QCheckBox(groupBoxTaskShowContent);
        checkBoxTaskHardDiskTemp->setObjectName(QString::fromUtf8("checkBoxTaskHardDiskTemp"));
        checkBoxTaskHardDiskTemp->setGeometry(QRect(210, 120, 180, 20));
        tabWidget->addTab(tabTaskBar, QString());

        verticalLayout->addWidget(tabWidget);

        Setting->setCentralWidget(centralwidget);

        retranslateUi(Setting);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QMainWindow *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));
        checkBoxAutoStart->setText(QCoreApplication::translate("Setting", "\345\274\200\346\234\272\350\207\252\345\220\257\345\212\250", nullptr));
        comboBoxLanguage->setItemText(0, QCoreApplication::translate("Setting", "\347\256\200\344\275\223\344\270\255\346\226\207", nullptr));
        comboBoxLanguage->setItemText(1, QCoreApplication::translate("Setting", "\347\271\201\344\275\223\344\270\255\346\226\207", nullptr));
        comboBoxLanguage->setItemText(2, QCoreApplication::translate("Setting", "\350\213\261\346\226\207", nullptr));

        labelLanguage->setText(QCoreApplication::translate("Setting", "\350\257\255\350\250\200\357\274\232", nullptr));
        comboBoxStockShow->setItemText(0, QCoreApplication::translate("Setting", "\347\272\242\346\266\250\347\273\277\350\267\214", nullptr));
        comboBoxStockShow->setItemText(1, QCoreApplication::translate("Setting", "\347\272\242\350\267\214\347\273\277\346\266\250", nullptr));

        labelStockShow->setText(QCoreApplication::translate("Setting", "\350\207\252\351\200\211\350\202\241\351\242\234\350\211\262\357\274\232", nullptr));
        labelFont->setText(QCoreApplication::translate("Setting", "\347\252\227\345\217\243\345\255\227\344\275\223\357\274\232", nullptr));
        pushButtonSetFont->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
        labelHotkey->setText(QCoreApplication::translate("Setting", "\345\277\253\346\215\267\351\224\256\350\256\276\347\275\256\357\274\232", nullptr));
        pushButtonSetHotkey->setText(QCoreApplication::translate("Setting", "\350\256\276\347\275\256\345\277\253\346\215\267\351\224\256", nullptr));
        pushButtonSetScreenProtect->setText(QCoreApplication::translate("Setting", "\350\256\276\347\275\256\345\261\217\345\271\225\344\277\235\346\212\244", nullptr));
        label->setText(QCoreApplication::translate("Setting", "\346\263\250\346\204\217\357\274\232\351\203\250\345\210\206\345\267\262\347\273\217\345\212\240\350\275\275\347\232\204\347\225\214\351\235\242\345\234\250\344\277\256\346\224\271\350\257\255\350\250\200\343\200\201\345\255\227\344\275\223\345\222\214\346\225\260\346\215\256\350\275\256\346\222\255\346\227\266\351\227\264\347\232\204\346\227\266\345\200\231\351\234\200\350\246\201\351\207\215\345\220\257\345\272\224\347\224\250\347\250\213\345\272\217\346\211\215\350\203\275\347\224\237\346\225\210", nullptr));
        labelFontResult->setText(QString());
        checkBoxFontWeight->setText(QCoreApplication::translate("Setting", "\345\212\240\347\262\227", nullptr));
        checkBoxQuickLook->setText(QCoreApplication::translate("Setting", "\345\220\257\347\224\250QuickLook", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Setting", "\345\261\217\345\271\225\344\272\256\345\272\246\344\270\216\345\257\271\346\257\224\345\272\246", nullptr));
        labelMonitor->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\350\246\201\350\260\203\350\212\202\347\232\204\345\261\217\345\271\225\357\274\232", nullptr));
        labelMonitorBrightness->setText(QCoreApplication::translate("Setting", "\350\256\276\347\275\256\345\261\217\345\271\225\344\272\256\345\272\246\357\274\232", nullptr));
        labelMonitorContrast->setText(QCoreApplication::translate("Setting", "\350\256\276\347\275\256\345\261\217\345\271\225\345\257\271\346\257\224\345\272\246\357\274\232", nullptr));
        labelMonitorBrightnessValue->setText(QString());
        labelMonitorContrastValue->setText(QString());
        label_4->setText(QCoreApplication::translate("Setting", "\346\225\260\346\215\256\350\275\256\346\222\255\346\227\266\351\227\264\357\274\232", nullptr));
        comboBoxUpdateTime->setItemText(0, QCoreApplication::translate("Setting", "1000ms", nullptr));
        comboBoxUpdateTime->setItemText(1, QCoreApplication::translate("Setting", "2000ms", nullptr));
        comboBoxUpdateTime->setItemText(2, QCoreApplication::translate("Setting", "3000ms", nullptr));
        comboBoxUpdateTime->setItemText(3, QCoreApplication::translate("Setting", "4000ms", nullptr));
        comboBoxUpdateTime->setItemText(4, QCoreApplication::translate("Setting", "5000ms", nullptr));
        comboBoxUpdateTime->setItemText(5, QCoreApplication::translate("Setting", "7000ms", nullptr));
        comboBoxUpdateTime->setItemText(6, QCoreApplication::translate("Setting", "10000ms", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("Setting", "\345\270\270\350\247\204\350\256\276\347\275\256", nullptr));
        groupBoxMainFontAndColor->setTitle(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\344\270\216\351\242\234\350\211\262", nullptr));
        label_5->setText(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Setting", "\346\226\207\346\234\254\351\242\234\350\211\262\357\274\232", nullptr));
        pushButtonMainChooseFont->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
        pushButtonMainChooseColor->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        labelMainFont->setText(QString());
        labelMainColor->setText(QString());
        label_9->setText(QCoreApplication::translate("Setting", "\350\203\214\346\231\257\351\242\234\350\211\262\357\274\232", nullptr));
        pushButtonMainChooseColorBK->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        labelMainColorBK->setText(QString());
        groupBoxMainShowContent->setTitle(QCoreApplication::translate("Setting", "\346\230\276\347\244\272\351\200\211\351\241\271", nullptr));
        groupBoxTaskShowContent_2->setTitle(QCoreApplication::translate("Setting", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        checkBoxMainCPUUtil->setText(QCoreApplication::translate("Setting", "CPU\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxMainMemoryUtil->setText(QCoreApplication::translate("Setting", "\345\206\205\345\255\230\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxMainUploadSpeed->setText(QCoreApplication::translate("Setting", "\344\270\212\344\274\240\351\200\237\345\272\246", nullptr));
        checkBoxMainDownloadSpeed->setText(QCoreApplication::translate("Setting", "\344\270\213\350\275\275\351\200\237\345\272\246", nullptr));
        checkBoxMainCPUTemp->setText(QCoreApplication::translate("Setting", "CPU\346\240\270\345\277\203\346\270\251\345\272\246", nullptr));
        checkBoxMainCPUPower->setText(QCoreApplication::translate("Setting", "CPU\345\212\237\347\216\207", nullptr));
        checkBoxMainGPUTemp->setText(QCoreApplication::translate("Setting", "GPU\346\240\270\345\277\203\346\270\251\345\272\246", nullptr));
        checkBoxMainGPUPower->setText(QCoreApplication::translate("Setting", "GPU\345\212\237\347\216\207", nullptr));
        checkBoxMainGPUUtil->setText(QCoreApplication::translate("Setting", "GPU\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxMainMBTemp->setText(QCoreApplication::translate("Setting", "\344\270\273\346\235\277\346\270\251\345\272\246", nullptr));
        checkBoxMainMBFan->setText(QCoreApplication::translate("Setting", "\344\270\273\346\235\277\351\243\216\346\211\207\350\275\254\351\200\237", nullptr));
        checkBoxMainHardDiskTemp->setText(QCoreApplication::translate("Setting", "\347\241\254\347\233\230\346\270\251\345\272\246", nullptr));
        groupBoxMainOther->setTitle(QCoreApplication::translate("Setting", "\345\205\266\344\273\226", nullptr));
        label_7->setText(QCoreApplication::translate("Setting", "\345\217\214\345\207\273\345\212\250\344\275\234\357\274\232", nullptr));
        checkBoxHideMainWindow->setText(QCoreApplication::translate("Setting", "\346\234\211\347\250\213\345\272\217\345\205\250\345\261\217\346\227\266\351\232\220\350\227\217\344\270\273\347\252\227\345\217\243", nullptr));
        comboBoxMainDoubleClickAction->setItemText(0, QCoreApplication::translate("Setting", "\351\273\230\350\256\244\346\265\217\350\247\210\345\231\250", nullptr));
        comboBoxMainDoubleClickAction->setItemText(1, QCoreApplication::translate("Setting", "\346\210\252\345\233\276\345\267\245\345\205\267", nullptr));
        comboBoxMainDoubleClickAction->setItemText(2, QCoreApplication::translate("Setting", "\344\276\277\345\210\251\350\264\264", nullptr));
        comboBoxMainDoubleClickAction->setItemText(3, QCoreApplication::translate("Setting", "\351\242\234\350\211\262\346\213\276\345\217\226", nullptr));
        comboBoxMainDoubleClickAction->setItemText(4, QCoreApplication::translate("Setting", "\344\273\273\345\212\241\347\256\241\347\220\206\345\231\250", nullptr));
        comboBoxMainDoubleClickAction->setItemText(5, QCoreApplication::translate("Setting", "\345\256\236\347\224\250\345\267\245\345\205\267", nullptr));
        comboBoxMainDoubleClickAction->setItemText(6, QCoreApplication::translate("Setting", "\345\256\232\346\227\266\346\217\220\351\206\222", nullptr));
        comboBoxMainDoubleClickAction->setItemText(7, QCoreApplication::translate("Setting", "\347\203\255\351\224\256\347\256\241\347\220\206", nullptr));
        comboBoxMainDoubleClickAction->setItemText(8, QCoreApplication::translate("Setting", "\350\207\252\351\200\211\350\202\241", nullptr));
        comboBoxMainDoubleClickAction->setItemText(9, QCoreApplication::translate("Setting", "\346\237\245\347\234\213\347\241\254\344\273\266\344\277\241\346\201\257", nullptr));
        comboBoxMainDoubleClickAction->setItemText(10, QCoreApplication::translate("Setting", "\345\210\207\346\215\242\345\210\222\350\257\215\347\277\273\350\257\221\347\212\266\346\200\201", nullptr));
        comboBoxMainDoubleClickAction->setItemText(11, QCoreApplication::translate("Setting", "\346\230\276\347\244\272\346\220\234\347\264\242\346\241\206", nullptr));
        comboBoxMainDoubleClickAction->setItemText(12, QCoreApplication::translate("Setting", "\350\207\252\345\256\232\344\271\211\346\211\223\345\274\200\347\250\213\345\272\217", nullptr));

        label_2->setText(QCoreApplication::translate("Setting", "\345\217\214\345\207\273\346\211\223\345\274\200\347\250\213\345\272\217\350\267\257\345\276\204\357\274\232", nullptr));
        labelMainDoubleClickPath->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabMainWindow), QCoreApplication::translate("Setting", "\344\270\273\347\252\227\345\217\243\350\256\276\347\275\256", nullptr));
        groupBoxTaskOther->setTitle(QCoreApplication::translate("Setting", "\345\205\266\344\273\226", nullptr));
        label_12->setText(QCoreApplication::translate("Setting", "\345\217\214\345\207\273\345\212\250\344\275\234\357\274\232", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(0, QCoreApplication::translate("Setting", "\351\273\230\350\256\244\346\265\217\350\247\210\345\231\250", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(1, QCoreApplication::translate("Setting", "\346\210\252\345\233\276\345\267\245\345\205\267", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(2, QCoreApplication::translate("Setting", "\344\276\277\345\210\251\350\264\264", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(3, QCoreApplication::translate("Setting", "\351\242\234\350\211\262\346\213\276\345\217\226", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(4, QCoreApplication::translate("Setting", "\344\273\273\345\212\241\347\256\241\347\220\206\345\231\250", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(5, QCoreApplication::translate("Setting", "\345\256\236\347\224\250\345\267\245\345\205\267", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(6, QCoreApplication::translate("Setting", "\345\256\232\346\227\266\346\217\220\351\206\222", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(7, QCoreApplication::translate("Setting", "\347\203\255\351\224\256\347\256\241\347\220\206", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(8, QCoreApplication::translate("Setting", "\350\207\252\351\200\211\350\202\241", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(9, QCoreApplication::translate("Setting", "\346\237\245\347\234\213\347\241\254\344\273\266\344\277\241\346\201\257", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(10, QCoreApplication::translate("Setting", "\345\210\207\346\215\242\345\210\222\350\257\215\347\277\273\350\257\221\347\212\266\346\200\201", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(11, QCoreApplication::translate("Setting", "\346\230\276\347\244\272\346\220\234\347\264\242\346\241\206", nullptr));
        comboBoxTaskDoubleClickAction->setItemText(12, QCoreApplication::translate("Setting", "\350\207\252\345\256\232\344\271\211\346\211\223\345\274\200\347\250\213\345\272\217", nullptr));

        label_3->setText(QCoreApplication::translate("Setting", "\345\217\214\345\207\273\346\211\223\345\274\200\347\250\213\345\272\217\350\267\257\345\276\204\357\274\232", nullptr));
        labelTaskDoubleClickPath->setText(QString());
        groupBoxTaskFontAndColor->setTitle(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\344\270\216\351\242\234\350\211\262", nullptr));
        label_13->setText(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\357\274\232", nullptr));
        label_14->setText(QCoreApplication::translate("Setting", "\346\226\207\346\234\254\351\242\234\350\211\262\357\274\232", nullptr));
        pushButtonTaskChooseFont->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
        pushButtonTaskChooseColor->setText(QCoreApplication::translate("Setting", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        labelTaskFont->setText(QString());
        labelTaskColor->setText(QString());
        groupBoxTaskShowInfo->setTitle(QCoreApplication::translate("Setting", "\346\230\276\347\244\272\351\200\211\351\241\271", nullptr));
        groupBoxTaskShowContent->setTitle(QCoreApplication::translate("Setting", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        checkBoxTaskCPUUtil->setText(QCoreApplication::translate("Setting", "CPU\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxTaskMemoryUtil->setText(QCoreApplication::translate("Setting", "\345\206\205\345\255\230\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxTaskUploadSpeed->setText(QCoreApplication::translate("Setting", "\344\270\212\344\274\240\351\200\237\345\272\246", nullptr));
        checkBoxTaskDownloadSpeed->setText(QCoreApplication::translate("Setting", "\344\270\213\350\275\275\351\200\237\345\272\246", nullptr));
        checkBoxTaskCPUTemp->setText(QCoreApplication::translate("Setting", "CPU\346\240\270\345\277\203\346\270\251\345\272\246", nullptr));
        checkBoxTaskCPUPower->setText(QCoreApplication::translate("Setting", "CPU\345\212\237\347\216\207", nullptr));
        checkBoxTaskGPUTemp->setText(QCoreApplication::translate("Setting", "GPU\346\240\270\345\277\203\346\270\251\345\272\246", nullptr));
        checkBoxTaskGPUPower->setText(QCoreApplication::translate("Setting", "GPU\345\212\237\347\216\207", nullptr));
        checkBoxTaskGPUUtil->setText(QCoreApplication::translate("Setting", "GPU\344\275\277\347\224\250\347\216\207", nullptr));
        checkBoxTaskMBTemp->setText(QCoreApplication::translate("Setting", "\344\270\273\346\235\277\346\270\251\345\272\246", nullptr));
        checkBoxTaskMBFan->setText(QCoreApplication::translate("Setting", "\344\270\273\346\235\277\351\243\216\346\211\207\350\275\254\351\200\237", nullptr));
        checkBoxTaskHardDiskTemp->setText(QCoreApplication::translate("Setting", "\347\241\254\347\233\230\346\270\251\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTaskBar), QCoreApplication::translate("Setting", "\344\273\273\345\212\241\346\240\217\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
