/********************************************************************************
** Form generated from reading UI file 'shortcutsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTCUTSETDIALOG_H
#define UI_SHORTCUTSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ShortcutSetDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditScreenShot;
    QLineEdit *lineEditStickyNote;
    QLineEdit *lineEditColorPicker;
    QLineEdit *lineEditTaskManager;
    QLineEdit *lineEditMainTool;
    QLineEdit *lineEditReminder;
    QLineEdit *lineEditHotkeyManager;
    QLineEdit *lineEditStock;
    QLineEdit *lineEditHardware;
    QLabel *labelScreenShot;
    QLabel *labelStickyNote;
    QLabel *labelTaskManager;
    QLabel *labelColorPicker;
    QLabel *labelHotkeyManager;
    QLabel *labelReminder;
    QLabel *labelHardware;
    QLabel *labelStock;
    QLabel *labelMainTool;
    QLineEdit *lineEditTranslator;
    QLabel *labelHardwareTranslator;
    QLineEdit *lineEditSearch;
    QLabel *labelSearch;
    QLabel *labelScreenShotTip;
    QLabel *labelStickyNoteTip;
    QLabel *labelTaskManagerTip;
    QLabel *labelMainToolTip;
    QLabel *labelColorPickerTip;
    QLabel *labelTranslatorTip;
    QLabel *labelHotkeyManagerTip;
    QLabel *labelStockTip;
    QLabel *labelHardwareTip;
    QLabel *labelReminderTip;
    QLabel *labelSearchTip;

    void setupUi(QDialog *ShortcutSetDialog)
    {
        if (ShortcutSetDialog->objectName().isEmpty())
            ShortcutSetDialog->setObjectName(QString::fromUtf8("ShortcutSetDialog"));
        ShortcutSetDialog->resize(400, 400);
        buttonBox = new QDialogButtonBox(ShortcutSetDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 360, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEditScreenShot = new QLineEdit(ShortcutSetDialog);
        lineEditScreenShot->setObjectName(QString::fromUtf8("lineEditScreenShot"));
        lineEditScreenShot->setGeometry(QRect(170, 20, 150, 25));
        lineEditStickyNote = new QLineEdit(ShortcutSetDialog);
        lineEditStickyNote->setObjectName(QString::fromUtf8("lineEditStickyNote"));
        lineEditStickyNote->setGeometry(QRect(170, 50, 150, 25));
        lineEditColorPicker = new QLineEdit(ShortcutSetDialog);
        lineEditColorPicker->setObjectName(QString::fromUtf8("lineEditColorPicker"));
        lineEditColorPicker->setGeometry(QRect(170, 80, 150, 25));
        lineEditTaskManager = new QLineEdit(ShortcutSetDialog);
        lineEditTaskManager->setObjectName(QString::fromUtf8("lineEditTaskManager"));
        lineEditTaskManager->setGeometry(QRect(170, 110, 150, 25));
        lineEditMainTool = new QLineEdit(ShortcutSetDialog);
        lineEditMainTool->setObjectName(QString::fromUtf8("lineEditMainTool"));
        lineEditMainTool->setGeometry(QRect(170, 140, 150, 25));
        lineEditReminder = new QLineEdit(ShortcutSetDialog);
        lineEditReminder->setObjectName(QString::fromUtf8("lineEditReminder"));
        lineEditReminder->setGeometry(QRect(170, 170, 150, 25));
        lineEditHotkeyManager = new QLineEdit(ShortcutSetDialog);
        lineEditHotkeyManager->setObjectName(QString::fromUtf8("lineEditHotkeyManager"));
        lineEditHotkeyManager->setGeometry(QRect(170, 200, 150, 25));
        lineEditStock = new QLineEdit(ShortcutSetDialog);
        lineEditStock->setObjectName(QString::fromUtf8("lineEditStock"));
        lineEditStock->setGeometry(QRect(170, 230, 150, 25));
        lineEditHardware = new QLineEdit(ShortcutSetDialog);
        lineEditHardware->setObjectName(QString::fromUtf8("lineEditHardware"));
        lineEditHardware->setGeometry(QRect(170, 260, 150, 25));
        labelScreenShot = new QLabel(ShortcutSetDialog);
        labelScreenShot->setObjectName(QString::fromUtf8("labelScreenShot"));
        labelScreenShot->setGeometry(QRect(20, 20, 150, 25));
        labelStickyNote = new QLabel(ShortcutSetDialog);
        labelStickyNote->setObjectName(QString::fromUtf8("labelStickyNote"));
        labelStickyNote->setGeometry(QRect(20, 50, 150, 25));
        labelTaskManager = new QLabel(ShortcutSetDialog);
        labelTaskManager->setObjectName(QString::fromUtf8("labelTaskManager"));
        labelTaskManager->setGeometry(QRect(20, 110, 150, 25));
        labelColorPicker = new QLabel(ShortcutSetDialog);
        labelColorPicker->setObjectName(QString::fromUtf8("labelColorPicker"));
        labelColorPicker->setGeometry(QRect(20, 80, 150, 25));
        labelHotkeyManager = new QLabel(ShortcutSetDialog);
        labelHotkeyManager->setObjectName(QString::fromUtf8("labelHotkeyManager"));
        labelHotkeyManager->setGeometry(QRect(20, 200, 150, 25));
        labelReminder = new QLabel(ShortcutSetDialog);
        labelReminder->setObjectName(QString::fromUtf8("labelReminder"));
        labelReminder->setGeometry(QRect(20, 170, 150, 25));
        labelHardware = new QLabel(ShortcutSetDialog);
        labelHardware->setObjectName(QString::fromUtf8("labelHardware"));
        labelHardware->setGeometry(QRect(20, 260, 150, 25));
        labelStock = new QLabel(ShortcutSetDialog);
        labelStock->setObjectName(QString::fromUtf8("labelStock"));
        labelStock->setGeometry(QRect(20, 230, 150, 25));
        labelMainTool = new QLabel(ShortcutSetDialog);
        labelMainTool->setObjectName(QString::fromUtf8("labelMainTool"));
        labelMainTool->setGeometry(QRect(20, 140, 150, 25));
        lineEditTranslator = new QLineEdit(ShortcutSetDialog);
        lineEditTranslator->setObjectName(QString::fromUtf8("lineEditTranslator"));
        lineEditTranslator->setGeometry(QRect(170, 320, 150, 25));
        labelHardwareTranslator = new QLabel(ShortcutSetDialog);
        labelHardwareTranslator->setObjectName(QString::fromUtf8("labelHardwareTranslator"));
        labelHardwareTranslator->setGeometry(QRect(20, 320, 150, 25));
        lineEditSearch = new QLineEdit(ShortcutSetDialog);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));
        lineEditSearch->setGeometry(QRect(170, 290, 150, 25));
        labelSearch = new QLabel(ShortcutSetDialog);
        labelSearch->setObjectName(QString::fromUtf8("labelSearch"));
        labelSearch->setGeometry(QRect(20, 290, 150, 25));
        labelScreenShotTip = new QLabel(ShortcutSetDialog);
        labelScreenShotTip->setObjectName(QString::fromUtf8("labelScreenShotTip"));
        labelScreenShotTip->setGeometry(QRect(330, 20, 60, 25));
        labelStickyNoteTip = new QLabel(ShortcutSetDialog);
        labelStickyNoteTip->setObjectName(QString::fromUtf8("labelStickyNoteTip"));
        labelStickyNoteTip->setGeometry(QRect(330, 50, 60, 25));
        labelTaskManagerTip = new QLabel(ShortcutSetDialog);
        labelTaskManagerTip->setObjectName(QString::fromUtf8("labelTaskManagerTip"));
        labelTaskManagerTip->setGeometry(QRect(330, 110, 60, 25));
        labelMainToolTip = new QLabel(ShortcutSetDialog);
        labelMainToolTip->setObjectName(QString::fromUtf8("labelMainToolTip"));
        labelMainToolTip->setGeometry(QRect(330, 140, 60, 25));
        labelColorPickerTip = new QLabel(ShortcutSetDialog);
        labelColorPickerTip->setObjectName(QString::fromUtf8("labelColorPickerTip"));
        labelColorPickerTip->setGeometry(QRect(330, 80, 60, 25));
        labelTranslatorTip = new QLabel(ShortcutSetDialog);
        labelTranslatorTip->setObjectName(QString::fromUtf8("labelTranslatorTip"));
        labelTranslatorTip->setGeometry(QRect(330, 320, 60, 25));
        labelHotkeyManagerTip = new QLabel(ShortcutSetDialog);
        labelHotkeyManagerTip->setObjectName(QString::fromUtf8("labelHotkeyManagerTip"));
        labelHotkeyManagerTip->setGeometry(QRect(330, 200, 60, 25));
        labelStockTip = new QLabel(ShortcutSetDialog);
        labelStockTip->setObjectName(QString::fromUtf8("labelStockTip"));
        labelStockTip->setGeometry(QRect(330, 230, 60, 25));
        labelHardwareTip = new QLabel(ShortcutSetDialog);
        labelHardwareTip->setObjectName(QString::fromUtf8("labelHardwareTip"));
        labelHardwareTip->setGeometry(QRect(330, 260, 60, 25));
        labelReminderTip = new QLabel(ShortcutSetDialog);
        labelReminderTip->setObjectName(QString::fromUtf8("labelReminderTip"));
        labelReminderTip->setGeometry(QRect(330, 170, 60, 25));
        labelSearchTip = new QLabel(ShortcutSetDialog);
        labelSearchTip->setObjectName(QString::fromUtf8("labelSearchTip"));
        labelSearchTip->setGeometry(QRect(330, 290, 60, 25));

        retranslateUi(ShortcutSetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ShortcutSetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ShortcutSetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ShortcutSetDialog);
    } // setupUi

    void retranslateUi(QDialog *ShortcutSetDialog)
    {
        ShortcutSetDialog->setWindowTitle(QCoreApplication::translate("ShortcutSetDialog", "Dialog", nullptr));
        labelScreenShot->setText(QCoreApplication::translate("ShortcutSetDialog", "\346\210\252\345\233\276\345\267\245\345\205\267\357\274\232", nullptr));
        labelStickyNote->setText(QCoreApplication::translate("ShortcutSetDialog", "\344\276\277\345\210\251\350\264\264\357\274\232", nullptr));
        labelTaskManager->setText(QCoreApplication::translate("ShortcutSetDialog", "\344\273\273\345\212\241\347\256\241\347\220\206\345\231\250\357\274\232", nullptr));
        labelColorPicker->setText(QCoreApplication::translate("ShortcutSetDialog", "\351\242\234\350\211\262\346\213\276\345\217\226\357\274\232", nullptr));
        labelHotkeyManager->setText(QCoreApplication::translate("ShortcutSetDialog", "\347\203\255\351\224\256\347\256\241\347\220\206\357\274\232", nullptr));
        labelReminder->setText(QCoreApplication::translate("ShortcutSetDialog", "\345\256\232\346\227\266\346\217\220\351\206\222\357\274\232", nullptr));
        labelHardware->setText(QCoreApplication::translate("ShortcutSetDialog", "\346\237\245\347\234\213\347\241\254\344\273\266\344\277\241\346\201\257\357\274\232", nullptr));
        labelStock->setText(QCoreApplication::translate("ShortcutSetDialog", "\350\207\252\351\200\211\350\202\241\357\274\232", nullptr));
        labelMainTool->setText(QCoreApplication::translate("ShortcutSetDialog", "\345\256\236\347\224\250\345\267\245\345\205\267\357\274\232", nullptr));
        labelHardwareTranslator->setText(QCoreApplication::translate("ShortcutSetDialog", "\345\210\222\350\257\215\347\277\273\350\257\221\357\274\232", nullptr));
        labelSearch->setText(QCoreApplication::translate("ShortcutSetDialog", "\346\220\234\347\264\242\345\267\245\345\205\267\357\274\232", nullptr));
        labelScreenShotTip->setText(QString());
        labelStickyNoteTip->setText(QString());
        labelTaskManagerTip->setText(QString());
        labelMainToolTip->setText(QString());
        labelColorPickerTip->setText(QString());
        labelTranslatorTip->setText(QString());
        labelHotkeyManagerTip->setText(QString());
        labelStockTip->setText(QString());
        labelHardwareTip->setText(QString());
        labelReminderTip->setText(QString());
        labelSearchTip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShortcutSetDialog: public Ui_ShortcutSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTCUTSETDIALOG_H
