#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setToolTip("Press the button to convert");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(convert()));
    mWeb = new QWebView(this);
    mWeb->setGeometry(0,0,200,200);
}

MainWindow::~MainWindow()
{
    delete mWeb;
    delete ui;
}

void MainWindow::convert()
{



    mTemplate["b1"] = "Lab 1";
    mTemplate["b2"] = "Lab 2";
    mTemplate["b3"] = "Lab 3";
    mTemplate["b4"] = "Lab 4";
    mTemplate["b5"] = "Lab 5";
    mTemplate["b6"] = "Lab 6";

    QString html = mTemplate.expandFile(":/SE-IC.html");
    QTextDocument document(html);
    QTextDocumentWriter writer("intermediate_data.html");
    writer.setFormat("plaintext");
    writer.write(&document);

    /*QFile file("intermediate_data.html");
    if ( !file.open( QIODevice::ReadWrite ) )
    {
        qWarning() << "Could not find file" << "intermediate_data.html";
        return;
    }

    file.seek(0);
    file.write(document.toHtml());
    file.close();*/
    //QMessageBox::information(0,"lol",document.toHtml());

    connect(mWeb,SIGNAL(loadFinished(bool)),this,SLOT(print()));
    mWeb->load(QUrl::fromLocalFile(QDir::currentPath() + "/intermediate_data.html"));
    this->setCentralWidget(mWeb);
}

void MainWindow::print()
{
    QPrinter printer;
    printer.setResolution(QPrinter::HighResolution);
    printer.setOutputFileName("output.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);

    mWeb->print(&printer);

}
