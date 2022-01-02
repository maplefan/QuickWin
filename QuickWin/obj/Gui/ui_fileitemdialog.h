/********************************************************************************
** Form generated from reading UI file 'fileitemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEITEMDIALOG_H
#define UI_FILEITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FileItemDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *videoName;
    QLabel *videoTime;
    QLabel *videoBitRate;
    QLabel *videoSize;

    void setupUi(QDialog *FileItemDialog)
    {
        if (FileItemDialog->objectName().isEmpty())
            FileItemDialog->setObjectName(QString::fromUtf8("FileItemDialog"));
        FileItemDialog->resize(381, 224);
        buttonBox = new QDialogButtonBox(FileItemDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(FileItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 111, 16));
        label_3 = new QLabel(FileItemDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 60, 72, 15));
        label_4 = new QLabel(FileItemDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 100, 91, 16));
        label_6 = new QLabel(FileItemDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 140, 72, 15));
        videoName = new QLabel(FileItemDialog);
        videoName->setObjectName(QString::fromUtf8("videoName"));
        videoName->setGeometry(QRect(150, 20, 211, 20));
        videoTime = new QLabel(FileItemDialog);
        videoTime->setObjectName(QString::fromUtf8("videoTime"));
        videoTime->setGeometry(QRect(160, 60, 171, 20));
        videoBitRate = new QLabel(FileItemDialog);
        videoBitRate->setObjectName(QString::fromUtf8("videoBitRate"));
        videoBitRate->setGeometry(QRect(160, 100, 191, 16));
        videoSize = new QLabel(FileItemDialog);
        videoSize->setObjectName(QString::fromUtf8("videoSize"));
        videoSize->setGeometry(QRect(160, 140, 191, 16));

        retranslateUi(FileItemDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FileItemDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FileItemDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FileItemDialog);
    } // setupUi

    void retranslateUi(QDialog *FileItemDialog)
    {
        FileItemDialog->setWindowTitle(QCoreApplication::translate("FileItemDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FileItemDialog", "\350\247\206\351\242\221\345\220\215\345\255\227\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("FileItemDialog", "\350\247\206\351\242\221\346\227\266\351\225\277\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("FileItemDialog", "\350\247\206\351\242\221\346\257\224\347\211\271\347\216\207\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("FileItemDialog", "\350\247\206\351\242\221\345\260\272\345\257\270\357\274\232", nullptr));
        videoName->setText(QString());
        videoTime->setText(QString());
        videoBitRate->setText(QString());
        videoSize->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileItemDialog: public Ui_FileItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEITEMDIALOG_H
