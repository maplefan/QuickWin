#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef OFFICEFORM_H
#define OFFICEFORM_H

#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QAxWidget>
#include <QAxSelect>
#include <QAxObject>
#include <QTabWidget>
#include <QScrollArea>
#include <QMessageBox>

//QAxwidget打开office和pdf

namespace Ui {
class OfficeForm;
}

class OfficeForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit OfficeForm(QWidget *parent = 0);
    ~OfficeForm();
    void OpenExcel(QString filename);
    void OpenWord(QString filename);
    void CloseOffice();

private slots:

private:
    Ui::OfficeForm *ui;
    QAxWidget* officeContent_ = nullptr;
    QAxObject* m_document = nullptr;

    void closeEvent(QCloseEvent *event);

private slots:
};

#endif // OFFICEFORM_H
