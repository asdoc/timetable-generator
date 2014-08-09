#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setToolTip("Press the button to convert");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(generate()));
    mWeb = new QWebView(this);
    mWeb->setGeometry(0,0,200,200);
}

MainWindow::~MainWindow()
{
    delete mWeb;
    delete ui;
}

void MainWindow::generate()
{
    vector <int> teachers_count[6];
    vector <string> teachers_name[6];

    teachers_count[1].push_back(3);
    teachers_count[1].push_back(3);
    teachers_count[1].push_back(3);
    teachers_count[1].push_back(3);
    teachers_count[1].push_back(2);
    teachers_count[1].push_back(1);
    teachers_count[1].push_back(1);

    teachers_count[2].push_back(6);
    teachers_count[2].push_back(5);
    teachers_count[2].push_back(3);
    teachers_count[2].push_back(2);

    teachers_count[3].push_back(6);
    teachers_count[3].push_back(4);
    teachers_count[3].push_back(3);
    teachers_count[3].push_back(3);

    teachers_count[4].push_back(6);
    teachers_count[4].push_back(3);
    teachers_count[4].push_back(3);
    teachers_count[4].push_back(2);
    teachers_count[4].push_back(2);

    teachers_count[5].push_back(6);
    teachers_count[5].push_back(4);
    teachers_count[5].push_back(4);
    teachers_count[5].push_back(2);

    teachers_name[1].push_back("pvh");
    teachers_name[1].push_back("ajj");
    teachers_name[1].push_back("n2");
    teachers_name[1].push_back("bdz");
    teachers_name[1].push_back("gvk");
    teachers_name[1].push_back("ard");
    teachers_name[1].push_back("kcw");

    teachers_name[2].push_back("pp");
    teachers_name[2].push_back("dms");
    teachers_name[2].push_back("ad");
    teachers_name[2].push_back("new");

    teachers_name[3].push_back("pvj");
    teachers_name[3].push_back("vvb");
    teachers_name[3].push_back("rak");
    teachers_name[3].push_back("ars");

    teachers_name[4].push_back("pht");
    teachers_name[4].push_back("pc");
    teachers_name[4].push_back("new3");
    teachers_name[4].push_back("ppj");
    teachers_name[4].push_back("ps");

    teachers_name[5].push_back("ddk");
    teachers_name[5].push_back("rvb");
    teachers_name[5].push_back("sng");
    teachers_name[5].push_back("ssh");

    timetable se;
    cout<<"Setting variables\n";

    for(int i=1;i<6;i++) {
        if(!se.set_teachers_lab(i,teachers_count[i],teachers_name[i])) {
            qDebug()<<"Unknown error\n";
            return;
        }
    }

    vector <int> t1;
    vector <string> t2;

    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("sss");
    t2.push_back("smg");
    t2.push_back("gvk");
    t2.push_back("bdz");
    se.set_teachers_lec(6,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(2);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("ard");
    t2.push_back("ajj");
    t2.push_back("kcw");
    se.set_teachers_lec(7,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(2);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("sng");
    t2.push_back("ddk");
    t2.push_back("ssh");
    se.set_teachers_lec(8,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(2);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("rak");
    t2.push_back("ars");
    t2.push_back("vvb");
    se.set_teachers_lec(9,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(2);
    t1.push_back(2);
    t2.push_back("dms");
    t2.push_back("pp");
    se.set_teachers_lec(10,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(4);
    t2.push_back("ppj");
    se.set_teachers_lec(11,t1,t2);

    qDebug()<<"Executing\n";
    se.execute();

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;i<5;k++)
            {
                QString str = "b" + QString::number(4*k + j + 1);
                if(se.is_lab(i,k,j))
                    mTemplate[str] = se.get_batch_timetable(i,k,j++).c_str();
                else
                {
                    QString html = QString(se.get_batch_timetable(i,k,j).c_str()) + QString("<br><br><hr/>") + QString(se.get_batch_timetable(i,k,j+1).c_str());
                    mTemplate[str] = html;
                    j++;
                }
            }
        }
    }

    convert();
}

void MainWindow::convert()
{


    /*mTemplate["b1"] =  "Lab 1 <br><br><hr/> Lab lol";
    mTemplate["b2"] = "Lab 2";
    mTemplate["b3"] = "Lab 3";
    mTemplate["b4"] = "Lab 4";
    mTemplate["b5"] = "Lab 5";
    mTemplate["b6"] = "Lab 6";*/

    QString html = mTemplate.expandFile(":/SE-I.html");
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
