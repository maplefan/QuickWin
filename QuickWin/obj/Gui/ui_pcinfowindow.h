/********************************************************************************
** Form generated from reading UI file 'pcinfowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCINFOWINDOW_H
#define UI_PCINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCInfoWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;

    void setupUi(QMainWindow *PCInfoWindow)
    {
        if (PCInfoWindow->objectName().isEmpty())
            PCInfoWindow->setObjectName(QString::fromUtf8("PCInfoWindow"));
        PCInfoWindow->resize(600, 500);
        centralwidget = new QWidget(PCInfoWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        PCInfoWindow->setCentralWidget(centralwidget);

        retranslateUi(PCInfoWindow);

        QMetaObject::connectSlotsByName(PCInfoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PCInfoWindow)
    {
        PCInfoWindow->setWindowTitle(QCoreApplication::translate("PCInfoWindow", "\347\241\254\344\273\266\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PCInfoWindow: public Ui_PCInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCINFOWINDOW_H
