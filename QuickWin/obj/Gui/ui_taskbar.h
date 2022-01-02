/********************************************************************************
** Form generated from reading UI file 'taskbar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKBAR_H
#define UI_TASKBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskBar
{
public:
    QWidget *centralWidget;
    QLabel *labelFirst;
    QLabel *labelSecond;
    QLabel *labelThird;
    QLabel *labelFourth;

    void setupUi(QMainWindow *TaskBar)
    {
        if (TaskBar->objectName().isEmpty())
            TaskBar->setObjectName(QString::fromUtf8("TaskBar"));
        TaskBar->resize(200, 50);
        TaskBar->setMinimumSize(QSize(200, 50));
        TaskBar->setMaximumSize(QSize(200, 50));
        centralWidget = new QWidget(TaskBar);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelFirst = new QLabel(centralWidget);
        labelFirst->setObjectName(QString::fromUtf8("labelFirst"));
        labelFirst->setGeometry(QRect(0, 0, 100, 25));
        labelFirst->setAlignment(Qt::AlignCenter);
        labelSecond = new QLabel(centralWidget);
        labelSecond->setObjectName(QString::fromUtf8("labelSecond"));
        labelSecond->setGeometry(QRect(100, 0, 100, 25));
        labelSecond->setAlignment(Qt::AlignCenter);
        labelThird = new QLabel(centralWidget);
        labelThird->setObjectName(QString::fromUtf8("labelThird"));
        labelThird->setGeometry(QRect(0, 25, 100, 25));
        labelThird->setAlignment(Qt::AlignCenter);
        labelFourth = new QLabel(centralWidget);
        labelFourth->setObjectName(QString::fromUtf8("labelFourth"));
        labelFourth->setGeometry(QRect(100, 25, 100, 25));
        labelFourth->setAlignment(Qt::AlignCenter);
        TaskBar->setCentralWidget(centralWidget);

        retranslateUi(TaskBar);

        QMetaObject::connectSlotsByName(TaskBar);
    } // setupUi

    void retranslateUi(QMainWindow *TaskBar)
    {
        TaskBar->setWindowTitle(QCoreApplication::translate("TaskBar", "TaskBar", nullptr));
        labelFirst->setText(QString());
        labelSecond->setText(QString());
        labelThird->setText(QString());
        labelFourth->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TaskBar: public Ui_TaskBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKBAR_H
