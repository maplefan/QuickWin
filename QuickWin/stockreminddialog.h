#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef STOCKREMINDDIALOG_H
#define STOCKREMINDDIALOG_H

#include <QDialog>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class StockRemindDialog;
}

class StockRemindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockRemindDialog(QString stockList , QWidget *parent = nullptr);
    ~StockRemindDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StockRemindDialog *ui;
    QString stockCode;

signals:
    void sendData(QString stockCode , QString info , QString data);
};

#endif // STOCKREMINDDIALOG_H
