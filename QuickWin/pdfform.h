#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef PDFFORM_H
#define PDFFORM_H
#include <QWidget>
#include <QKeyEvent>
#include <QScrollArea>
#include<cstring>
#include "PdfManager.h"
#include "PictureBox.h"
#include <QMainWindow>

namespace Ui {
class PDFForm;
}

class PDFForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDFForm(QString filename,QByteArray& bytearray, QWidget *parent = 0);
    ~PDFForm();

    //��ʼ��
    void InitFile();

    //����ҳ��
    bool LoadPage(int page);
    //�����¼�
    void wheelEvent(QWheelEvent *event);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    //����ҳ���ǩ
    void UpdateLabelPage();

private:
    Ui::PDFForm *ui;
    qint64 FileLength_ = 0;
    int CurrentPage_ = 0;
    int PageCount_ = 0;
    PictureBox* Picture_ = nullptr;
    std::string FileName_;
    char* File_ = nullptr;
    bool HaveLoadPdf_ = false; //�Ƿ��Ѿ�������pdf
    bool IsLoadSuccess = false;

private slots:
    void keyPressEvent(QKeyEvent *event)override;
    void scrollChange();//���ֵ�ֵ�ı��ʱ��
};

#endif // PDFFORM_H
