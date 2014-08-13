#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setToolTip("Press the button to convert");
    current_div = 1;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->NextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->PrevButton, SIGNAL(clicked()), this, SLOT(prev()));

    connect(ui->mWeb,SIGNAL(loadFinished(bool)),this,SLOT(print()));

    ui->NextButton->hide();
    ui->PrevButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString get_batch(int i)
{
    switch(i%4)
    {
        case 0:
            return QString(QString("(E") + QString::number(i/4 + 1) + QString(")"));
        case 1:
            return QString(QString("(F") + QString::number(i/4 + 1) + QString(")"));
        case 2:
            return QString(QString("(G") + QString::number(i/4 + 1) + QString(")"));
        case 3:
            return QString(QString("(H") + QString::number(i/4 + 1) + QString(")"));
    };
}

void MainWindow::generate()
{
    ui->statusBar->clearMessage();
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
    qDebug()<<"Setting variables\n";

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

    t1.clear();
    t2.clear();
    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("ajj");
    t2.push_back("pvh");
    t2.push_back("new7");
    t2.push_back("bdz");
    se.set_teachers_lec(12,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("vvb");
    t2.push_back("ars");
    t2.push_back("pvj");
    t2.push_back("rak");
    se.set_teachers_lec(13,t1,t2);

    t1.clear();
    t2.clear();
    t1.push_back(2);
    t1.push_back(1);
    t1.push_back(1);
    t2.push_back("sng");
    t2.push_back("ars");
    t2.push_back("rvb");
    se.set_teachers_lec(14,t1,t2);

    se.add_lab_name(1,"A208");
    se.add_lab_name(1,"A209");

    se.add_lab_name(2,"C004");

    se.add_lab_name(3,"A209");
    se.add_lab_name(3,"A306");

    se.add_lab_name(4,"SSL1");
    se.add_lab_name(4,"SSL2");

    se.add_lab_name(5,"A202");
    se.add_lab_name(5,"A203");

    qDebug()<<"Executing\n";
    se.execute();

    if(!se.success()) {
        qDebug()<<"An error occured: \n"<<se.get_error_log().c_str();
        ui->statusBar->showMessage("An error occured: " + QString(se.get_error_log().c_str()));
        return;
    }
    int count = 1;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<7;k++)
            {
                QString str = "b" + QString::number(count++);
                if(se.is_lab(i*4,j,k))
                {
                    mTemplate[str] = "";
                    for(int p=0;p<4;p++)
                    {
                        mTemplate[str] += QString(se.get_batch_timetable(i*4 + p,j,k).c_str() + get_batch(i*4 + p) + QString("<br>") );

                    }

                    k++;
                }
                else
                {
                    if(k<6)
                    {
                        QString html = QString(se.get_batch_timetable(i*4,j,k).c_str()) + QString("<br><br><hr/>") + QString(se.get_batch_timetable(i*4,j,k+1).c_str());
                        mTemplate[str] = html;
                        k++;
                    }
                    else if(k==6)
                    {
                        QString html = QString(se.get_batch_timetable(i*4,j,k).c_str());
                        mTemplate[str] = html;
                    }
                }
            }

        }
        count = 1;
        convert(i+1);
    }
    display(1);
    ui->NextButton->show();
    ui->PrevButton->show();
}

void MainWindow::convert(int div)
{


    /*mTemplate["b1"] =  "Lab 1 <br><br><hr/> Lab lol";
    mTemplate["b2"] = "Lab 2";
    mTemplate["b3"] = "Lab 3";
    mTemplate["b4"] = "Lab 4";
    mTemplate["b5"] = "Lab 5";
    mTemplate["b6"] = "Lab 6";*/
    QString html;
    mTemplate["div"] = QString::number(div);
    if(div!=4)
        html = mTemplate.expandFile(":/SE-I.html");
    else
        html = mTemplate.expandFile(":/SE-IV.html");
    QTextDocument document(html);
    QTextDocumentWriter writer("intermediate_data(division " + QString::number(div) + ").html");
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



}

void MainWindow::display(int div)
{
    qDebug()<<div;
    ui->mWeb->load(QUrl::fromLocalFile(QDir::currentPath() + "/intermediate_data(division " + QString::number(div) + ").html"));
    qDebug()<<QString(QDir::currentPath() + "/intermediate_data(division " + QString::number(div) + ").html");
}

void MainWindow::next()
{
    if(current_div<4)
    {
        display(current_div + 1);
        current_div++;
    }
    else return;
}

void MainWindow::prev()
{
    if(current_div>1)
    {
        current_div--;
        display(current_div);


    }
    else return;
}

void MainWindow::print()
{
    QPrinter printer;
    printer.setResolution(QPrinter::HighResolution);
    printer.setOutputFileName("output.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);

    ui->mWeb->print(&printer);

}
