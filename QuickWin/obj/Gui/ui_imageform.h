/********************************************************************************
** Form generated from reading UI file 'imageform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEFORM_H
#define UI_IMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageForm
{
public:
    QWidget *centralwidget;
    QLabel *label;

    void setupUi(QMainWindow *ImageForm)
    {
        if (ImageForm->objectName().isEmpty())
            ImageForm->setObjectName(QString::fromUtf8("ImageForm"));
        ImageForm->resize(800, 600);
        centralwidget = new QWidget(ImageForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 600));
        ImageForm->setCentralWidget(centralwidget);

        retranslateUi(ImageForm);

        QMetaObject::connectSlotsByName(ImageForm);
    } // setupUi

    void retranslateUi(QMainWindow *ImageForm)
    {
        ImageForm->setWindowTitle(QCoreApplication::translate("ImageForm", "MainWindow", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageForm: public Ui_ImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEFORM_H
