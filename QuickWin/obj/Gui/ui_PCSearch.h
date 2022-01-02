/********************************************************************************
** Form generated from reading UI file 'PCSearch.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCSEARCH_H
#define UI_PCSEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCSearch
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QTableView *tableView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PCSearch)
    {
        if (PCSearch->objectName().isEmpty())
            PCSearch->setObjectName(QString::fromUtf8("PCSearch"));
        PCSearch->resize(980, 620);
        PCSearch->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(PCSearch);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 960, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("border-radius:10px;"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 59, 960, 520));
        tableView->setStyleSheet(QString::fromUtf8(""));
        PCSearch->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(PCSearch);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PCSearch->setStatusBar(statusBar);

        retranslateUi(PCSearch);

        QMetaObject::connectSlotsByName(PCSearch);
    } // setupUi

    void retranslateUi(QMainWindow *PCSearch)
    {
        PCSearch->setWindowTitle(QCoreApplication::translate("PCSearch", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PCSearch: public Ui_PCSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCSEARCH_H
