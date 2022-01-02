/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelFirst;
    QLabel *labelSecond;
    QLabel *labelThird;
    QLabel *labelFourth;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(260, 70);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelFirst = new QLabel(centralWidget);
        labelFirst->setObjectName(QString::fromUtf8("labelFirst"));
        labelFirst->setGeometry(QRect(20, 10, 100, 20));
        labelSecond = new QLabel(centralWidget);
        labelSecond->setObjectName(QString::fromUtf8("labelSecond"));
        labelSecond->setGeometry(QRect(150, 10, 100, 20));
        labelThird = new QLabel(centralWidget);
        labelThird->setObjectName(QString::fromUtf8("labelThird"));
        labelThird->setGeometry(QRect(20, 40, 100, 20));
        labelFourth = new QLabel(centralWidget);
        labelFourth->setObjectName(QString::fromUtf8("labelFourth"));
        labelFourth->setGeometry(QRect(150, 40, 100, 20));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelFirst->setText(QCoreApplication::translate("MainWindow", "Loading...", nullptr));
        labelSecond->setText(QCoreApplication::translate("MainWindow", "Loading...", nullptr));
        labelThird->setText(QCoreApplication::translate("MainWindow", "Loading...", nullptr));
        labelFourth->setText(QCoreApplication::translate("MainWindow", "Loading...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
