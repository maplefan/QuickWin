/********************************************************************************
** Form generated from reading UI file 'hotkeymanage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOTKEYMANAGE_H
#define UI_HOTKEYMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HotkeyManage
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_1;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout_1;
    QLabel *labelComboBox;
    QComboBox *comboBox;
    QLabel *labelLineEdit;
    QLineEdit *lineEdit;

    void setupUi(QMainWindow *HotkeyManage)
    {
        if (HotkeyManage->objectName().isEmpty())
            HotkeyManage->setObjectName(QString::fromUtf8("HotkeyManage"));
        HotkeyManage->resize(800, 600);
        centralwidget = new QWidget(HotkeyManage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout_1->addWidget(treeView);


        verticalLayout->addLayout(verticalLayout_1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        labelComboBox = new QLabel(centralwidget);
        labelComboBox->setObjectName(QString::fromUtf8("labelComboBox"));

        horizontalLayout_1->addWidget(labelComboBox);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_1->addWidget(comboBox);

        labelLineEdit = new QLabel(centralwidget);
        labelLineEdit->setObjectName(QString::fromUtf8("labelLineEdit"));

        horizontalLayout_1->addWidget(labelLineEdit);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_1->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_1);


        verticalLayout_2->addLayout(verticalLayout);

        HotkeyManage->setCentralWidget(centralwidget);

        retranslateUi(HotkeyManage);

        QMetaObject::connectSlotsByName(HotkeyManage);
    } // setupUi

    void retranslateUi(QMainWindow *HotkeyManage)
    {
        HotkeyManage->setWindowTitle(QCoreApplication::translate("HotkeyManage", "MainWindow", nullptr));
        labelComboBox->setText(QCoreApplication::translate("HotkeyManage", "\350\277\207\346\273\244\351\241\271\357\274\232", nullptr));
        labelLineEdit->setText(QCoreApplication::translate("HotkeyManage", "\350\277\207\346\273\244\345\231\250\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HotkeyManage: public Ui_HotkeyManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOTKEYMANAGE_H
