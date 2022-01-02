/********************************************************************************
** Form generated from reading UI file 'timechoosedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMECHOOSEDIALOG_H
#define UI_TIMECHOOSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeChooseDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTimeEdit *timeEdit;
    QComboBox *comboBox;
    QWidget *widgetDate;
    QDateEdit *dateEdit;
    QLabel *label;
    QWidget *widgetEveryYear;
    QLabel *label_2;
    QLineEdit *lineEditYear;
    QLabel *label_7;
    QLineEdit *lineEditYear2;
    QLabel *label_8;
    QWidget *widgetEveryMonth;
    QLabel *label_3;
    QLabel *label_9;
    QLineEdit *lineEditMonth;
    QWidget *widgetEveryWeek;
    QLabel *label_4;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QWidget *widgetEveryDay;

    void setupUi(QDialog *TimeChooseDialog)
    {
        if (TimeChooseDialog->objectName().isEmpty())
            TimeChooseDialog->setObjectName(QString::fromUtf8("TimeChooseDialog"));
        TimeChooseDialog->resize(400, 158);
        buttonBox = new QDialogButtonBox(TimeChooseDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 120, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        timeEdit = new QTimeEdit(TimeChooseDialog);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(210, 10, 161, 31));
        comboBox = new QComboBox(TimeChooseDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 10, 161, 31));
        widgetDate = new QWidget(TimeChooseDialog);
        widgetDate->setObjectName(QString::fromUtf8("widgetDate"));
        widgetDate->setGeometry(QRect(30, 40, 341, 91));
        dateEdit = new QDateEdit(widgetDate);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(150, 20, 171, 41));
        label = new QLabel(widgetDate);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 81, 16));
        widgetEveryYear = new QWidget(TimeChooseDialog);
        widgetEveryYear->setObjectName(QString::fromUtf8("widgetEveryYear"));
        widgetEveryYear->setGeometry(QRect(30, 40, 341, 91));
        label_2 = new QLabel(widgetEveryYear);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 30, 81, 16));
        lineEditYear = new QLineEdit(widgetEveryYear);
        lineEditYear->setObjectName(QString::fromUtf8("lineEditYear"));
        lineEditYear->setGeometry(QRect(100, 20, 40, 40));
        label_7 = new QLabel(widgetEveryYear);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(160, 20, 40, 40));
        lineEditYear2 = new QLineEdit(widgetEveryYear);
        lineEditYear2->setObjectName(QString::fromUtf8("lineEditYear2"));
        lineEditYear2->setGeometry(QRect(230, 20, 40, 40));
        label_8 = new QLabel(widgetEveryYear);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(290, 20, 40, 40));
        widgetEveryMonth = new QWidget(TimeChooseDialog);
        widgetEveryMonth->setObjectName(QString::fromUtf8("widgetEveryMonth"));
        widgetEveryMonth->setGeometry(QRect(30, 40, 341, 91));
        label_3 = new QLabel(widgetEveryMonth);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 30, 81, 16));
        label_9 = new QLabel(widgetEveryMonth);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(160, 20, 40, 40));
        lineEditMonth = new QLineEdit(widgetEveryMonth);
        lineEditMonth->setObjectName(QString::fromUtf8("lineEditMonth"));
        lineEditMonth->setGeometry(QRect(100, 20, 40, 40));
        widgetEveryWeek = new QWidget(TimeChooseDialog);
        widgetEveryWeek->setObjectName(QString::fromUtf8("widgetEveryWeek"));
        widgetEveryWeek->setGeometry(QRect(30, 40, 341, 91));
        label_4 = new QLabel(widgetEveryWeek);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 30, 81, 16));
        checkBox_1 = new QCheckBox(widgetEveryWeek);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(100, 20, 71, 16));
        checkBox_2 = new QCheckBox(widgetEveryWeek);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(180, 20, 71, 16));
        checkBox_3 = new QCheckBox(widgetEveryWeek);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(260, 20, 71, 16));
        checkBox_4 = new QCheckBox(widgetEveryWeek);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(100, 40, 71, 16));
        checkBox_5 = new QCheckBox(widgetEveryWeek);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(180, 40, 71, 16));
        checkBox_6 = new QCheckBox(widgetEveryWeek);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(260, 40, 71, 16));
        checkBox_7 = new QCheckBox(widgetEveryWeek);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(100, 60, 71, 16));
        widgetEveryDay = new QWidget(TimeChooseDialog);
        widgetEveryDay->setObjectName(QString::fromUtf8("widgetEveryDay"));
        widgetEveryDay->setGeometry(QRect(30, 40, 341, 91));
        widgetDate->raise();
        buttonBox->raise();
        timeEdit->raise();
        comboBox->raise();
        widgetEveryDay->raise();
        widgetEveryYear->raise();
        widgetEveryMonth->raise();
        widgetEveryWeek->raise();

        retranslateUi(TimeChooseDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TimeChooseDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TimeChooseDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TimeChooseDialog);
    } // setupUi

    void retranslateUi(QDialog *TimeChooseDialog)
    {
        TimeChooseDialog->setWindowTitle(QCoreApplication::translate("TimeChooseDialog", "Dialog", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("TimeChooseDialog", "\346\214\207\345\256\232\346\227\245\346\234\237", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TimeChooseDialog", "\346\257\217\345\271\264", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("TimeChooseDialog", "\346\257\217\346\234\210", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("TimeChooseDialog", "\346\257\217\346\227\245", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237", nullptr));

        label->setText(QCoreApplication::translate("TimeChooseDialog", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("TimeChooseDialog", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("TimeChooseDialog", "\346\234\210", nullptr));
        label_8->setText(QCoreApplication::translate("TimeChooseDialog", "\346\227\245", nullptr));
        label_3->setText(QCoreApplication::translate("TimeChooseDialog", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("TimeChooseDialog", "\346\227\245", nullptr));
        label_4->setText(QCoreApplication::translate("TimeChooseDialog", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
        checkBox_1->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\344\270\200", nullptr));
        checkBox_2->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\344\272\214", nullptr));
        checkBox_3->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\344\270\211", nullptr));
        checkBox_4->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\345\233\233", nullptr));
        checkBox_5->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\344\272\224", nullptr));
        checkBox_6->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\345\205\255", nullptr));
        checkBox_7->setText(QCoreApplication::translate("TimeChooseDialog", "\346\230\237\346\234\237\345\244\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeChooseDialog: public Ui_TimeChooseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMECHOOSEDIALOG_H
