#include "htmlform.h"
#include "ui_htmlform.h"

HtmlForm::HtmlForm(QString filename , QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HtmlForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    m_webView = new QWebEngineView(this);
    QStackedLayout* layout = new QStackedLayout(ui->frame);
    ui->frame->setLayout(layout);
    layout->addWidget(m_webView);
    m_webView->load(QUrl::fromLocalFile(filename));
}

HtmlForm::~HtmlForm()
{
    delete ui;
}
