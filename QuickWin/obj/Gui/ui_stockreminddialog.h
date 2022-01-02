/********************************************************************************
** Form generated from reading UI file 'stockreminddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKREMINDDIALOG_H
#define UI_STOCKREMINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_StockRemindDialog
{
public:
    QDialogButtonBox *buttonBox;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QLineEdit *lineEditRate;
    QLineEdit *lineEditRise;
    QLineEdit *lineEditFall;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelTitle;
    QLabel *labelInfo;
    QLabel *label;

    void setupUi(QDialog *StockRemindDialog)
    {
        if (StockRemindDialog->objectName().isEmpty())
            StockRemindDialog->setObjectName(QString::fromUtf8("StockRemindDialog"));
        StockRemindDialog->resize(275, 220);
        buttonBox = new QDialogButtonBox(StockRemindDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 180, 221, 32));
        buttonBox->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        checkBox_1 = new QCheckBox(StockRemindDialog);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(10, 90, 150, 20));
        checkBox_1->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        checkBox_2 = new QCheckBox(StockRemindDialog);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(10, 120, 150, 20));
        checkBox_2->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        checkBox_3 = new QCheckBox(StockRemindDialog);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(10, 150, 150, 20));
        checkBox_3->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        lineEditRate = new QLineEdit(StockRemindDialog);
        lineEditRate->setObjectName(QString::fromUtf8("lineEditRate"));
        lineEditRate->setGeometry(QRect(160, 90, 70, 20));
        lineEditRate->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        lineEditRise = new QLineEdit(StockRemindDialog);
        lineEditRise->setObjectName(QString::fromUtf8("lineEditRise"));
        lineEditRise->setGeometry(QRect(160, 120, 70, 20));
        lineEditRise->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        lineEditFall = new QLineEdit(StockRemindDialog);
        lineEditFall->setObjectName(QString::fromUtf8("lineEditFall"));
        lineEditFall->setGeometry(QRect(160, 150, 70, 20));
        lineEditFall->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        label_1 = new QLabel(StockRemindDialog);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(240, 90, 54, 20));
        label_1->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        label_2 = new QLabel(StockRemindDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 120, 54, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        label_3 = new QLabel(StockRemindDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 150, 54, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        labelTitle = new QLabel(StockRemindDialog);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setGeometry(QRect(20, 10, 180, 20));
        labelTitle->setStyleSheet(QString::fromUtf8("font: 25 12pt \"Microsoft YaHei\";"));
        labelInfo = new QLabel(StockRemindDialog);
        labelInfo->setObjectName(QString::fromUtf8("labelInfo"));
        labelInfo->setGeometry(QRect(20, 40, 180, 20));
        labelInfo->setStyleSheet(QString::fromUtf8("font: 25 11pt \"Microsoft YaHei\";"));
        label = new QLabel(StockRemindDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 150, 12));

        retranslateUi(StockRemindDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StockRemindDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StockRemindDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StockRemindDialog);
    } // setupUi

    void retranslateUi(QDialog *StockRemindDialog)
    {
        StockRemindDialog->setWindowTitle(QCoreApplication::translate("StockRemindDialog", "Dialog", nullptr));
        checkBox_1->setText(QCoreApplication::translate("StockRemindDialog", "\345\274\200\347\233\230\345\220\216\346\266\250\350\267\214\345\271\205\350\266\205\350\277\207", nullptr));
        checkBox_2->setText(QCoreApplication::translate("StockRemindDialog", "\350\202\241\344\273\267\344\270\212\346\266\250\350\276\276\345\210\260\346\210\226\351\253\230\344\272\216", nullptr));
        checkBox_3->setText(QCoreApplication::translate("StockRemindDialog", "\350\202\241\344\273\267\344\270\213\350\267\214\350\276\276\345\210\260\346\210\226\344\275\216\344\272\216", nullptr));
        label_1->setText(QCoreApplication::translate("StockRemindDialog", "%", nullptr));
        label_2->setText(QCoreApplication::translate("StockRemindDialog", "\345\205\203", nullptr));
        label_3->setText(QCoreApplication::translate("StockRemindDialog", "\345\205\203", nullptr));
        labelTitle->setText(QString());
        labelInfo->setText(QString());
        label->setText(QCoreApplication::translate("StockRemindDialog", "(\344\270\200\346\235\241\350\256\276\347\275\256\346\234\200\345\244\232\346\217\220\347\244\272\344\270\200\346\254\241)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockRemindDialog: public Ui_StockRemindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKREMINDDIALOG_H
