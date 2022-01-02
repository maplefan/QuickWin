/********************************************************************************
** Form generated from reading UI file 'snappit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAPPIT_H
#define UI_SNAPPIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_snappit
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_open;
    QPushButton *pushButton_shortcut;

    void setupUi(QWidget *snappit)
    {
        if (snappit->objectName().isEmpty())
            snappit->setObjectName(QString::fromUtf8("snappit"));
        snappit->resize(350, 360);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(snappit->sizePolicy().hasHeightForWidth());
        snappit->setSizePolicy(sizePolicy);
        snappit->setMinimumSize(QSize(350, 360));
        snappit->setMaximumSize(QSize(350, 360));
        gridLayout = new QGridLayout(snappit);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_open = new QPushButton(snappit);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));

        gridLayout->addWidget(pushButton_open, 0, 0, 1, 1);

        pushButton_shortcut = new QPushButton(snappit);
        pushButton_shortcut->setObjectName(QString::fromUtf8("pushButton_shortcut"));

        gridLayout->addWidget(pushButton_shortcut, 1, 0, 1, 1);


        retranslateUi(snappit);

        QMetaObject::connectSlotsByName(snappit);
    } // setupUi

    void retranslateUi(QWidget *snappit)
    {
        snappit->setWindowTitle(QCoreApplication::translate("snappit", "snappit", nullptr));
        pushButton_open->setText(QCoreApplication::translate("snappit", "\346\211\223\345\274\200", nullptr));
        pushButton_shortcut->setText(QCoreApplication::translate("snappit", "\346\210\252\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class snappit: public Ui_snappit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAPPIT_H
