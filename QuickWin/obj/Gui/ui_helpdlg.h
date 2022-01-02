/********************************************************************************
** Form generated from reading UI file 'helpdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDLG_H
#define UI_HELPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpDlg
{
public:
    QWidget *centralwidget;
    QLabel *infoLabel;
    QLabel *copyrightLabel;
    QPushButton *authorBtn;
    QPushButton *githubBtn;
    QPushButton *BlogBtn;
    QPushButton *donateBtn;
    QPushButton *thanksBtn;
    QPushButton *okBtn;
    QLabel *labelBuildTime;

    void setupUi(QMainWindow *HelpDlg)
    {
        if (HelpDlg->objectName().isEmpty())
            HelpDlg->setObjectName(QString::fromUtf8("HelpDlg"));
        HelpDlg->resize(360, 211);
        centralwidget = new QWidget(HelpDlg);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(30, 10, 241, 20));
        copyrightLabel = new QLabel(centralwidget);
        copyrightLabel->setObjectName(QString::fromUtf8("copyrightLabel"));
        copyrightLabel->setGeometry(QRect(30, 50, 231, 20));
        authorBtn = new QPushButton(centralwidget);
        authorBtn->setObjectName(QString::fromUtf8("authorBtn"));
        authorBtn->setGeometry(QRect(20, 130, 93, 28));
        githubBtn = new QPushButton(centralwidget);
        githubBtn->setObjectName(QString::fromUtf8("githubBtn"));
        githubBtn->setGeometry(QRect(130, 130, 93, 28));
        BlogBtn = new QPushButton(centralwidget);
        BlogBtn->setObjectName(QString::fromUtf8("BlogBtn"));
        BlogBtn->setGeometry(QRect(240, 130, 93, 28));
        donateBtn = new QPushButton(centralwidget);
        donateBtn->setObjectName(QString::fromUtf8("donateBtn"));
        donateBtn->setGeometry(QRect(20, 170, 93, 28));
        thanksBtn = new QPushButton(centralwidget);
        thanksBtn->setObjectName(QString::fromUtf8("thanksBtn"));
        thanksBtn->setGeometry(QRect(130, 170, 93, 28));
        okBtn = new QPushButton(centralwidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(240, 170, 93, 28));
        labelBuildTime = new QLabel(centralwidget);
        labelBuildTime->setObjectName(QString::fromUtf8("labelBuildTime"));
        labelBuildTime->setGeometry(QRect(30, 90, 251, 20));
        HelpDlg->setCentralWidget(centralwidget);

        retranslateUi(HelpDlg);

        QMetaObject::connectSlotsByName(HelpDlg);
    } // setupUi

    void retranslateUi(QMainWindow *HelpDlg)
    {
        HelpDlg->setWindowTitle(QCoreApplication::translate("HelpDlg", "MainWindow", nullptr));
        infoLabel->setText(QCoreApplication::translate("HelpDlg", "QuickWindows  1.0.0\347\211\210\346\234\254 (x86)", nullptr));
        copyrightLabel->setText(QCoreApplication::translate("HelpDlg", "Copyright (C) 2021 By maplefan", nullptr));
        authorBtn->setText(QCoreApplication::translate("HelpDlg", "\350\201\224\347\263\273\344\275\234\350\200\205", nullptr));
        githubBtn->setText(QCoreApplication::translate("HelpDlg", "Github", nullptr));
        BlogBtn->setText(QCoreApplication::translate("HelpDlg", "\345\215\232\345\256\242", nullptr));
        donateBtn->setText(QCoreApplication::translate("HelpDlg", "\346\215\220\345\212\251", nullptr));
        thanksBtn->setText(QCoreApplication::translate("HelpDlg", "\351\270\243\350\260\242", nullptr));
        okBtn->setText(QCoreApplication::translate("HelpDlg", "\347\241\256\345\256\232", nullptr));
        labelBuildTime->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelpDlg: public Ui_HelpDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDLG_H
