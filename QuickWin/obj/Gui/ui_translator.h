/********************************************************************************
** Form generated from reading UI file 'translator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSLATOR_H
#define UI_TRANSLATOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TranslatorDlg
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TranslatorDlg)
    {
        if (TranslatorDlg->objectName().isEmpty())
            TranslatorDlg->setObjectName(QString::fromUtf8("TranslatorDlg"));
        TranslatorDlg->resize(387, 274);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        TranslatorDlg->setWindowIcon(icon);
        centralWidget = new QWidget(TranslatorDlg);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TranslatorDlg->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TranslatorDlg);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 387, 26));
        TranslatorDlg->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TranslatorDlg);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TranslatorDlg->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TranslatorDlg);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TranslatorDlg->setStatusBar(statusBar);

        retranslateUi(TranslatorDlg);

        QMetaObject::connectSlotsByName(TranslatorDlg);
    } // setupUi

    void retranslateUi(QMainWindow *TranslatorDlg)
    {
        TranslatorDlg->setWindowTitle(QCoreApplication::translate("TranslatorDlg", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TranslatorDlg: public Ui_TranslatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSLATOR_H
