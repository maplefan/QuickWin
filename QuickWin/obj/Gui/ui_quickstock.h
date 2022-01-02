/********************************************************************************
** Form generated from reading UI file 'quickstock.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKSTOCK_H
#define UI_QUICKSTOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickStock
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QMainWindow *QuickStock)
    {
        if (QuickStock->objectName().isEmpty())
            QuickStock->setObjectName(QString::fromUtf8("QuickStock"));
        QuickStock->resize(300, 400);
        centralwidget = new QWidget(QuickStock);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMaximumSize(QSize(16777215, 16777215));
        tableView->setStyleSheet(QString::fromUtf8("/*QTableView \345\267\246\344\270\212\350\247\222\346\240\267\345\274\217*/\n"
"QTableView QTableCornerButton::section {\n"
"   /*  background: red;\n"
"    border: 2px outset red;*/\n"
"    color: red;\n"
"    background-color: rgb(64, 64, 64);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(64, 64, 64);\n"
" }\n"
"\n"
" QTableView {\n"
"    color: white;                                       /*\350\241\250\346\240\274\345\206\205\346\226\207\345\255\227\351\242\234\350\211\262*/\n"
"    gridline-color: black;                              /*\350\241\250\346\240\274\345\206\205\346\241\206\351\242\234\350\211\262*/\n"
"    background-color: rgb(108, 108, 108);               /*\350\241\250\346\240\274\345\206\205\350\203\214\346\231\257\350\211\262*/\n"
"    alternate-background-color: rgb(64, 64, 64);\n"
"    selection-color: white;                             /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\346\226\207\345\255\227\351\242\234\350\211\262*/"
                        "\n"
"    selection-background-color: rgb(77, 77, 77);        /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\350\203\214\346\231\257\350\211\262*/\n"
"    border: 2px groove gray;\n"
"    border-radius: 0px;\n"
"    padding: 2px 4px;\n"
"}\n"
"\n"
"QHeaderView {\n"
"    color: white;\n"
"    background-color: rgb(108, 108, 108);\n"
"    border: 0px solid rgb(144, 144, 144);\n"
"    border:0px solid rgb(191,191,191);\n"
"    border-left-color: rgba(255, 255, 255, 0);\n"
"    border-top-color: rgba(255, 255, 255, 0);\n"
"    border-radius:0px;\n"
"    min-height:29px;	\n"
"	font: bold 10pt\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    color: white;\n"
"    background-color: rgb(64, 64, 64);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(64, 64, 64);\n"
"} "));

        verticalLayout->addWidget(tableView);

        QuickStock->setCentralWidget(centralwidget);

        retranslateUi(QuickStock);

        QMetaObject::connectSlotsByName(QuickStock);
    } // setupUi

    void retranslateUi(QMainWindow *QuickStock)
    {
        QuickStock->setWindowTitle(QCoreApplication::translate("QuickStock", "\350\207\252\351\200\211\350\202\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuickStock: public Ui_QuickStock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKSTOCK_H
