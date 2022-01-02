/********************************************************************************
** Form generated from reading UI file 'timereminddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEREMINDDIALOG_H
#define UI_TIMEREMINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_TimeRemindDialog
{
public:
    QPushButton *pushButtonReset;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QTextEdit *textEditEvent;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *editDuration;
    QTextEdit *textEditRemark;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonSound;
    QLabel *labelSoundPath;
    QLabel *label_6;
    QPushButton *pushButtonRemindTime;
    QPushButton *pushButtonPic;
    QLabel *label_7;
    QLabel *labelPicPath;
    QLabel *labelRemindTime;

    void setupUi(QDialog *TimeRemindDialog)
    {
        if (TimeRemindDialog->objectName().isEmpty())
            TimeRemindDialog->setObjectName(QString::fromUtf8("TimeRemindDialog"));
        TimeRemindDialog->resize(400, 400);
        pushButtonReset = new QPushButton(TimeRemindDialog);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setGeometry(QRect(50, 360, 75, 23));
        pushButtonOK = new QPushButton(TimeRemindDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(160, 360, 75, 23));
        pushButtonCancel = new QPushButton(TimeRemindDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(270, 360, 75, 23));
        textEditEvent = new QTextEdit(TimeRemindDialog);
        textEditEvent->setObjectName(QString::fromUtf8("textEditEvent"));
        textEditEvent->setGeometry(QRect(60, 10, 321, 91));
        label = new QLabel(TimeRemindDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 40, 16));
        label_2 = new QLabel(TimeRemindDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 118, 101, 16));
        editDuration = new QLineEdit(TimeRemindDialog);
        editDuration->setObjectName(QString::fromUtf8("editDuration"));
        editDuration->setGeometry(QRect(120, 116, 61, 20));
        textEditRemark = new QTextEdit(TimeRemindDialog);
        textEditRemark->setObjectName(QString::fromUtf8("textEditRemark"));
        textEditRemark->setGeometry(QRect(50, 270, 321, 81));
        label_3 = new QLabel(TimeRemindDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 280, 40, 12));
        label_4 = new QLabel(TimeRemindDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 203, 54, 16));
        pushButtonSound = new QPushButton(TimeRemindDialog);
        pushButtonSound->setObjectName(QString::fromUtf8("pushButtonSound"));
        pushButtonSound->setGeometry(QRect(90, 200, 75, 23));
        labelSoundPath = new QLabel(TimeRemindDialog);
        labelSoundPath->setObjectName(QString::fromUtf8("labelSoundPath"));
        labelSoundPath->setGeometry(QRect(180, 200, 200, 23));
        label_6 = new QLabel(TimeRemindDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(220, 118, 61, 16));
        pushButtonRemindTime = new QPushButton(TimeRemindDialog);
        pushButtonRemindTime->setObjectName(QString::fromUtf8("pushButtonRemindTime"));
        pushButtonRemindTime->setGeometry(QRect(290, 115, 75, 23));
        pushButtonPic = new QPushButton(TimeRemindDialog);
        pushButtonPic->setObjectName(QString::fromUtf8("pushButtonPic"));
        pushButtonPic->setGeometry(QRect(90, 235, 75, 23));
        label_7 = new QLabel(TimeRemindDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 238, 71, 16));
        labelPicPath = new QLabel(TimeRemindDialog);
        labelPicPath->setObjectName(QString::fromUtf8("labelPicPath"));
        labelPicPath->setGeometry(QRect(180, 235, 200, 23));
        labelRemindTime = new QLabel(TimeRemindDialog);
        labelRemindTime->setObjectName(QString::fromUtf8("labelRemindTime"));
        labelRemindTime->setGeometry(QRect(10, 150, 381, 40));

        retranslateUi(TimeRemindDialog);

        QMetaObject::connectSlotsByName(TimeRemindDialog);
    } // setupUi

    void retranslateUi(QDialog *TimeRemindDialog)
    {
        TimeRemindDialog->setWindowTitle(QCoreApplication::translate("TimeRemindDialog", "Dialog", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("TimeRemindDialog", "\351\207\215\347\275\256", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("TimeRemindDialog", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("TimeRemindDialog", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("TimeRemindDialog", "\344\272\213\344\273\266\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("TimeRemindDialog", "\346\217\220\351\206\222\346\227\266\351\225\277\357\274\210\347\247\222\357\274\211\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("TimeRemindDialog", "\345\244\207\346\263\250\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("TimeRemindDialog", "\346\217\220\351\206\222\345\243\260\351\237\263\357\274\232", nullptr));
        pushButtonSound->setText(QCoreApplication::translate("TimeRemindDialog", "\351\200\211\346\213\251", nullptr));
        labelSoundPath->setText(QString());
        label_6->setText(QCoreApplication::translate("TimeRemindDialog", "\346\217\220\351\206\222\346\227\266\351\227\264\357\274\232", nullptr));
        pushButtonRemindTime->setText(QCoreApplication::translate("TimeRemindDialog", "\351\200\211\346\213\251", nullptr));
        pushButtonPic->setText(QCoreApplication::translate("TimeRemindDialog", "\351\200\211\346\213\251", nullptr));
        label_7->setText(QCoreApplication::translate("TimeRemindDialog", "\350\207\252\345\256\232\344\271\211\351\231\204\345\233\276\357\274\232", nullptr));
        labelPicPath->setText(QString());
        labelRemindTime->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TimeRemindDialog: public Ui_TimeRemindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEREMINDDIALOG_H
