/********************************************************************************
** Form generated from reading UI file 'fileform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEFORM_H
#define UI_FILEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileForm
{
public:
    QWidget *centralwidget;
    QLabel *img;
    QLabel *name;
    QLabel *createtime;
    QLabel *lastreadtime;
    QLabel *size;

    void setupUi(QMainWindow *FileForm)
    {
        if (FileForm->objectName().isEmpty())
            FileForm->setObjectName(QString::fromUtf8("FileForm"));
        FileForm->resize(400, 150);
        centralwidget = new QWidget(FileForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        img = new QLabel(centralwidget);
        img->setObjectName(QString::fromUtf8("img"));
        img->setGeometry(QRect(10, 10, 128, 128));
        name = new QLabel(centralwidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(150, 5, 800, 32));
        createtime = new QLabel(centralwidget);
        createtime->setObjectName(QString::fromUtf8("createtime"));
        createtime->setGeometry(QRect(150, 45, 800, 20));
        QFont font;
        font.setBold(false);
        createtime->setFont(font);
        lastreadtime = new QLabel(centralwidget);
        lastreadtime->setObjectName(QString::fromUtf8("lastreadtime"));
        lastreadtime->setGeometry(QRect(150, 70, 800, 20));
        size = new QLabel(centralwidget);
        size->setObjectName(QString::fromUtf8("size"));
        size->setGeometry(QRect(150, 95, 800, 20));
        FileForm->setCentralWidget(centralwidget);

        retranslateUi(FileForm);

        QMetaObject::connectSlotsByName(FileForm);
    } // setupUi

    void retranslateUi(QMainWindow *FileForm)
    {
        FileForm->setWindowTitle(QCoreApplication::translate("FileForm", "MainWindow", nullptr));
        img->setText(QString());
        name->setText(QString());
        createtime->setText(QString());
        lastreadtime->setText(QString());
        size->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileForm: public Ui_FileForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEFORM_H
