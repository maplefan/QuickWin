/********************************************************************************
** Form generated from reading UI file 'addstockdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTOCKDIALOG_H
#define UI_ADDSTOCKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddStockDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QDialog *AddStockDialog)
    {
        if (AddStockDialog->objectName().isEmpty())
            AddStockDialog->setObjectName(QString::fromUtf8("AddStockDialog"));
        AddStockDialog->resize(280, 170);
        buttonBox = new QDialogButtonBox(AddStockDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(25, 130, 200, 30));
        buttonBox->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(AddStockDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(182, 100, 81, 24));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));
        label = new QLabel(AddStockDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 241, 80));
        label->setStyleSheet(QString::fromUtf8("font: 25 11pt \"Microsoft YaHei\";"));
        label->setWordWrap(true);
        comboBox = new QComboBox(AddStockDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 100, 151, 24));
        comboBox->setStyleSheet(QString::fromUtf8("font: 25 10pt \"Microsoft YaHei\";"));

        retranslateUi(AddStockDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddStockDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddStockDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddStockDialog);
    } // setupUi

    void retranslateUi(QDialog *AddStockDialog)
    {
        AddStockDialog->setWindowTitle(QCoreApplication::translate("AddStockDialog", "\345\242\236\345\212\240\350\202\241\347\245\250", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("AddStockDialog", "01810", nullptr));
        label->setText(QCoreApplication::translate("AddStockDialog", "\350\257\267\350\276\223\345\205\245\350\202\241\347\245\250\344\273\243\347\240\201\357\274\232\346\232\202\346\227\266\344\273\205\346\224\257\346\214\201\346\270\257\350\202\241\343\200\201\347\276\216\350\202\241\343\200\201A\350\202\241\343\200\202", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("AddStockDialog", "\346\270\257\350\202\241", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddStockDialog", "\347\276\216\350\202\241", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("AddStockDialog", "A\350\202\241", nullptr));

    } // retranslateUi

};

namespace Ui {
    class AddStockDialog: public Ui_AddStockDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTOCKDIALOG_H
