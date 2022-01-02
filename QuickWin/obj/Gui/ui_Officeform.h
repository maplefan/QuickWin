/********************************************************************************
** Form generated from reading UI file 'Officeform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OFFICEFORM_H
#define UI_OFFICEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OfficeForm
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;

    void setupUi(QMainWindow *OfficeForm)
    {
        if (OfficeForm->objectName().isEmpty())
            OfficeForm->setObjectName(QString::fromUtf8("OfficeForm"));
        OfficeForm->resize(952, 614);
        centralWidget = new QWidget(OfficeForm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);

        OfficeForm->setCentralWidget(centralWidget);

        retranslateUi(OfficeForm);

        QMetaObject::connectSlotsByName(OfficeForm);
    } // setupUi

    void retranslateUi(QMainWindow *OfficeForm)
    {
        OfficeForm->setWindowTitle(QCoreApplication::translate("OfficeForm", "\346\227\240\346\240\207\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OfficeForm: public Ui_OfficeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OFFICEFORM_H
