/********************************************************************************
** Form generated from reading UI file 'networkinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKINFO_H
#define UI_NETWORKINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkInfo
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;

    void setupUi(QMainWindow *NetworkInfo)
    {
        if (NetworkInfo->objectName().isEmpty())
            NetworkInfo->setObjectName(QString::fromUtf8("NetworkInfo"));
        NetworkInfo->resize(500, 300);
        centralwidget = new QWidget(NetworkInfo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        NetworkInfo->setCentralWidget(centralwidget);

        retranslateUi(NetworkInfo);

        QMetaObject::connectSlotsByName(NetworkInfo);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkInfo)
    {
        NetworkInfo->setWindowTitle(QCoreApplication::translate("NetworkInfo", "\350\277\236\346\216\245\350\257\246\346\203\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkInfo: public Ui_NetworkInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKINFO_H
