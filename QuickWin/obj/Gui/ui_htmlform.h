/********************************************************************************
** Form generated from reading UI file 'htmlform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTMLFORM_H
#define UI_HTMLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HtmlForm
{
public:
    QWidget *centralwidget;
    QFrame *frame;

    void setupUi(QMainWindow *HtmlForm)
    {
        if (HtmlForm->objectName().isEmpty())
            HtmlForm->setObjectName(QString::fromUtf8("HtmlForm"));
        HtmlForm->resize(800, 600);
        centralwidget = new QWidget(HtmlForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-1, -1, 801, 601));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        HtmlForm->setCentralWidget(centralwidget);

        retranslateUi(HtmlForm);

        QMetaObject::connectSlotsByName(HtmlForm);
    } // setupUi

    void retranslateUi(QMainWindow *HtmlForm)
    {
        HtmlForm->setWindowTitle(QCoreApplication::translate("HtmlForm", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HtmlForm: public Ui_HtmlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTMLFORM_H
