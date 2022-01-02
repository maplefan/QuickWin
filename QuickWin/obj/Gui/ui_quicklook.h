/********************************************************************************
** Form generated from reading UI file 'quicklook.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKLOOK_H
#define UI_QUICKLOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickLook
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *QuickLook)
    {
        if (QuickLook->objectName().isEmpty())
            QuickLook->setObjectName(QString::fromUtf8("QuickLook"));
        QuickLook->resize(400, 300);
        centralWidget = new QWidget(QuickLook);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QuickLook->setCentralWidget(centralWidget);

        retranslateUi(QuickLook);

        QMetaObject::connectSlotsByName(QuickLook);
    } // setupUi

    void retranslateUi(QMainWindow *QuickLook)
    {
        QuickLook->setWindowTitle(QCoreApplication::translate("QuickLook", "QuickLook", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuickLook: public Ui_QuickLook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKLOOK_H
