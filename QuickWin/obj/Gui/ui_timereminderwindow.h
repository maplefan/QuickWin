/********************************************************************************
** Form generated from reading UI file 'timereminderwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEREMINDERWINDOW_H
#define UI_TIMEREMINDERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeReminderWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_1;
    QVBoxLayout *verticalLayout_1;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelPic;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelEvent;
    QLabel *labelRemarks;
    QLabel *labelTimeStr;

    void setupUi(QMainWindow *TimeReminderWindow)
    {
        if (TimeReminderWindow->objectName().isEmpty())
            TimeReminderWindow->setObjectName(QString::fromUtf8("TimeReminderWindow"));
        TimeReminderWindow->resize(800, 600);
        centralwidget = new QWidget(TimeReminderWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelPic = new QLabel(centralwidget);
        labelPic->setObjectName(QString::fromUtf8("labelPic"));

        horizontalLayout_6->addWidget(labelPic);


        horizontalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelEvent = new QLabel(centralwidget);
        labelEvent->setObjectName(QString::fromUtf8("labelEvent"));
        labelEvent->setStyleSheet(QString::fromUtf8("font: 25 36pt \"Microsoft YaHei\";\n"
"qproperty-alignment: 'AlignCenter';"));

        verticalLayout_2->addWidget(labelEvent);

        labelRemarks = new QLabel(centralwidget);
        labelRemarks->setObjectName(QString::fromUtf8("labelRemarks"));
        labelRemarks->setStyleSheet(QString::fromUtf8("font: 25 36pt \"Microsoft YaHei\";\n"
"qproperty-alignment: 'AlignCenter';"));

        verticalLayout_2->addWidget(labelRemarks);

        labelTimeStr = new QLabel(centralwidget);
        labelTimeStr->setObjectName(QString::fromUtf8("labelTimeStr"));
        labelTimeStr->setStyleSheet(QString::fromUtf8("font: 25 36pt \"Microsoft YaHei\";\n"
"qproperty-alignment: 'AlignCenter';"));

        verticalLayout_2->addWidget(labelTimeStr);


        horizontalLayout_5->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_1->addLayout(horizontalLayout_4);


        horizontalLayout_1->addLayout(verticalLayout_1);


        verticalLayout_3->addLayout(horizontalLayout_1);

        TimeReminderWindow->setCentralWidget(centralwidget);

        retranslateUi(TimeReminderWindow);

        QMetaObject::connectSlotsByName(TimeReminderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TimeReminderWindow)
    {
        TimeReminderWindow->setWindowTitle(QCoreApplication::translate("TimeReminderWindow", "MainWindow", nullptr));
        labelPic->setText(QString());
        labelEvent->setText(QString());
        labelRemarks->setText(QString());
        labelTimeStr->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TimeReminderWindow: public Ui_TimeReminderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEREMINDERWINDOW_H
