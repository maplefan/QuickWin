/********************************************************************************
** Form generated from reading UI file 'timereminder.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEREMINDER_H
#define UI_TIMEREMINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeReminder
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QMainWindow *TimeReminder)
    {
        if (TimeReminder->objectName().isEmpty())
            TimeReminder->setObjectName(QString::fromUtf8("TimeReminder"));
        TimeReminder->resize(400, 500);
        centralwidget = new QWidget(TimeReminder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        TimeReminder->setCentralWidget(centralwidget);

        retranslateUi(TimeReminder);

        QMetaObject::connectSlotsByName(TimeReminder);
    } // setupUi

    void retranslateUi(QMainWindow *TimeReminder)
    {
        TimeReminder->setWindowTitle(QCoreApplication::translate("TimeReminder", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeReminder: public Ui_TimeReminder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEREMINDER_H
