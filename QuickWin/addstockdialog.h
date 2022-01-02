#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef ADDSTOCKDIALOG_H
#define ADDSTOCKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class AddStockDialog;
}

class AddStockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStockDialog(QString stockConfig ,QWidget *parent = nullptr );
    ~AddStockDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void sendData(QString data );

private:
    Ui::AddStockDialog *ui;
    QString stockConfig;
};

#endif // ADDSTOCKDIALOG_H
