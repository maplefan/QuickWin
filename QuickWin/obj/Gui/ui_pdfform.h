/********************************************************************************
** Form generated from reading UI file 'pdfform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFFORM_H
#define UI_PDFFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDFForm
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_1;
    QScrollBar *verticalScrollBar;

    void setupUi(QMainWindow *PDFForm)
    {
        if (PDFForm->objectName().isEmpty())
            PDFForm->setObjectName(QString::fromUtf8("PDFForm"));
        PDFForm->resize(600, 600);
        centralwidget = new QWidget(PDFForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));

        horizontalLayout->addLayout(verticalLayout_1);

        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalScrollBar);


        verticalLayout->addLayout(horizontalLayout);

        PDFForm->setCentralWidget(centralwidget);

        retranslateUi(PDFForm);

        QMetaObject::connectSlotsByName(PDFForm);
    } // setupUi

    void retranslateUi(QMainWindow *PDFForm)
    {
        PDFForm->setWindowTitle(QCoreApplication::translate("PDFForm", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PDFForm: public Ui_PDFForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFFORM_H
