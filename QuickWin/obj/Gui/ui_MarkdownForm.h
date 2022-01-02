/********************************************************************************
** Form generated from reading UI file 'MarkdownForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKDOWNFORM_H
#define UI_MARKDOWNFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MarkdownForm
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionSaveAs;
    QAction *actionNew;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QPlainTextEdit *editor;
    QWebEngineView *preview;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MarkdownForm)
    {
        if (MarkdownForm->objectName().isEmpty())
            MarkdownForm->setObjectName(QString::fromUtf8("MarkdownForm"));
        MarkdownForm->resize(800, 600);
        actionOpen = new QAction(MarkdownForm);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MarkdownForm);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionExit = new QAction(MarkdownForm);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSaveAs = new QAction(MarkdownForm);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionNew = new QAction(MarkdownForm);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralwidget = new QWidget(MarkdownForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        editor = new QPlainTextEdit(splitter);
        editor->setObjectName(QString::fromUtf8("editor"));
        splitter->addWidget(editor);
        preview = new QWebEngineView(splitter);
        preview->setObjectName(QString::fromUtf8("preview"));
        splitter->addWidget(preview);

        horizontalLayout->addWidget(splitter);

        MarkdownForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MarkdownForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MarkdownForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MarkdownForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MarkdownForm->setStatusBar(statusbar);

        retranslateUi(MarkdownForm);

        QMetaObject::connectSlotsByName(MarkdownForm);
    } // setupUi

    void retranslateUi(QMainWindow *MarkdownForm)
    {
        MarkdownForm->setWindowTitle(QCoreApplication::translate("MarkdownForm", "QuickLook", nullptr));
        actionOpen->setText(QCoreApplication::translate("MarkdownForm", "&Open...", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MarkdownForm", "Open document", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MarkdownForm", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MarkdownForm", "&Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MarkdownForm", "Save current document", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MarkdownForm", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MarkdownForm", "E&xit", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MarkdownForm", "Exit editor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MarkdownForm", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSaveAs->setText(QCoreApplication::translate("MarkdownForm", "Save &As...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveAs->setToolTip(QCoreApplication::translate("MarkdownForm", "Save document under different name", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNew->setText(QCoreApplication::translate("MarkdownForm", "&New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MarkdownForm", "Create new document", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MarkdownForm", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class MarkdownForm: public Ui_MarkdownForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKDOWNFORM_H
