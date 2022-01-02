/********************************************************************************
** Form generated from reading UI file 'taskmgr.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMGR_H
#define UI_TASKMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskMgr
{
public:
    QAction *actionShutdown;
    QAction *actionReboot;
    QAction *actionLogout;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabProcess;
    QWidget *tabWindow;
    QMenuBar *menuBar;
    QMenu *menu1;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskMgr)
    {
        if (TaskMgr->objectName().isEmpty())
            TaskMgr->setObjectName(QString::fromUtf8("TaskMgr"));
        TaskMgr->resize(700, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaskMgr->sizePolicy().hasHeightForWidth());
        TaskMgr->setSizePolicy(sizePolicy);
        actionShutdown = new QAction(TaskMgr);
        actionShutdown->setObjectName(QString::fromUtf8("actionShutdown"));
        actionReboot = new QAction(TaskMgr);
        actionReboot->setObjectName(QString::fromUtf8("actionReboot"));
        actionLogout = new QAction(TaskMgr);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        centralWidget = new QWidget(TaskMgr);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(14, 10, 671, 421));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabProcess = new QWidget();
        tabProcess->setObjectName(QString::fromUtf8("tabProcess"));
        sizePolicy.setHeightForWidth(tabProcess->sizePolicy().hasHeightForWidth());
        tabProcess->setSizePolicy(sizePolicy);
        tabWidget->addTab(tabProcess, QString());
        tabWindow = new QWidget();
        tabWindow->setObjectName(QString::fromUtf8("tabWindow"));
        sizePolicy.setHeightForWidth(tabWindow->sizePolicy().hasHeightForWidth());
        tabWindow->setSizePolicy(sizePolicy);
        tabWidget->addTab(tabWindow, QString());
        TaskMgr->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TaskMgr);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 22));
        menu1 = new QMenu(menuBar);
        menu1->setObjectName(QString::fromUtf8("menu1"));
        TaskMgr->setMenuBar(menuBar);
        statusBar = new QStatusBar(TaskMgr);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TaskMgr->setStatusBar(statusBar);

        menuBar->addAction(menu1->menuAction());
        menu1->addAction(actionShutdown);
        menu1->addAction(actionReboot);
        menu1->addAction(actionLogout);

        retranslateUi(TaskMgr);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(TaskMgr);
    } // setupUi

    void retranslateUi(QMainWindow *TaskMgr)
    {
        TaskMgr->setWindowTitle(QCoreApplication::translate("TaskMgr", "MainWindow", nullptr));
        actionShutdown->setText(QCoreApplication::translate("TaskMgr", "\345\205\263\346\234\272", nullptr));
        actionReboot->setText(QCoreApplication::translate("TaskMgr", "\351\207\215\345\220\257", nullptr));
        actionLogout->setText(QCoreApplication::translate("TaskMgr", "\346\263\250\351\224\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabProcess), QCoreApplication::translate("TaskMgr", "\350\277\233\347\250\213\345\210\227\350\241\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWindow), QCoreApplication::translate("TaskMgr", "\347\252\227\345\217\243\344\277\241\346\201\257", nullptr));
        menu1->setTitle(QCoreApplication::translate("TaskMgr", "\351\200\211\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskMgr: public Ui_TaskMgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMGR_H
