#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setToolTip("Press the button to convert");

    progress = new QProgressDialog("Generating timetable...", "", 0, 0, this);
    progress->setModal(true);
    progress->setCancelButton(0);

    current_div = 1;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->NextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->PrevButton, SIGNAL(clicked()), this, SLOT(prev()));
    connect(ui->PrintButton, SIGNAL(clicked()), this, SLOT(print()));
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(menubar(QAction*)));









    //connect(ui->mWeb,SIGNAL(loadFinished(bool)),this,SLOT(print()));


    ui->NextButton->hide();
    ui->PrevButton->hide();
    ui->PrintButton->hide();;
    ui->mWeb->hide();

}

MainWindow::~MainWindow()
{
    delete progress;
    delete ui;
}

void MainWindow::menubar(QAction *action)
{
    if(action->text() == "Exit") this->close();
    else if(action->text() == "About")
    {
        QMessageBox::about(this,"Time Table Generator", "Timetable generator program\nCredits:\n1. Aditya Sarode\n2. Aaryaman Vasishta\n3. Akhil Koul");
    }
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


void MainWindow::start_timer()
{
    progress->show();
}

void MainWindow::generate()
{

    //thread->start();
    progress->show();
    QApplication::processEvents();

    while(!execute());
    progress->cancel();
    //thread->terminate();
}

/*
bool MainWindow::execute()
{
    ui->statusBar->showMessage("Executing... ");
    ui->mWeb->show();
    ui->label_2->hide();
    mTemplate.clear();

    QApplication::processEvents();
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
            return false;
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
        return false;
    }

    ui->statusBar->showMessage("Timetable generated.");



    //Set lectures
    int count = 1;
    for(int i=0;i<4;i++)
    {
        mTemplate.clear();
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<7;k++)
            {
                QString str = "b" + QString::number(count++);

                //Divisions 1-3
                if(i<3)
                {
                    if(i==0&&j==5&&k==6)
                    {
                        qDebug()<<"lol";
                        //lol


                    }
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
                            mTemplate[str] = html == "         " || html == ""?html:html + "*";

                        }
                    }
                }
                else       //Special case for division 4
                {
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

                        if(k>0)
                        {
                            QString html = QString(se.get_batch_timetable(i*4,j,k).c_str()) + QString("<br><br><hr/>") + QString(se.get_batch_timetable(i*4,j,k+1).c_str());
                            mTemplate[str] = html;
                            k++;
                        }
                        else if(k==0)
                        {
                            QString html = QString(se.get_batch_timetable(i*4,j,k).c_str());
                            mTemplate[str] = html == "         " || html == ""?html:html + "*";
                        }
                    }
                }
            }
        }



        count = 1;
        //Set class room
        if(i<3)
            mTemplate["cl_room"] = se.get_class_room(i,1,1).c_str();

        //Set lab teacher names
        for(int p=0;p<4;p++)
        {
            for(int q=1;q<=5;q++)
            {

                int x = (i*4) + (p);
                if(x==16)
                {
                    x=15;
                    q=5;

                }
                QString str = "s" + QString::number(q) + QString::number(p+1);
                qDebug()<<str;
                mTemplate[str] = se.get_batch_lab_teacher(x ,q).c_str();
                //qDebug()<<se.get_batch_lab_teacher(x,p).c_str();
                str = "l" + QString::number(q) + QString::number(p+1);
                mTemplate[str] = se.get_batch_lab_name(x,q).c_str();
            }
        }

        //Set lecture subject teacher names
        for(int p=6;p<15;p++)
        {
            QString str = "t" + QString::number(p-5);
            mTemplate[str] = se.get_class_lec_teacher(i,p).c_str();
        }

        //Create HTML output
        convert(i+1);
    }
    display(current_div);
    ui->NextButton->show();
    ui->PrintButton->show();
    ui->PrevButton->show();
    ui->ExitButton->show();

    return true;
}
*/

bool MainWindow::execute()
{
    ui->statusBar->showMessage("Executing... ");
    ui->mWeb->show();
    ui->label_2->hide();
    mTemplate.clear();

    QApplication::processEvents();

    vector <int> teachers_count[6];
    vector <string> teachers_name[6];


    for(int i=1;i<=5;i++) {
        sqlite3 *db;
        sqlite3_stmt * stmt;
        if (sqlite3_open("../timetable.db", &db) == SQLITE_OK) {
            char i_buf[1024];
            sprintf(i_buf,"%d",i);
            string i_str(i_buf);
            string select_stmt = "select a.name,b.load from assignment b inner join teacher a on a.teacher_id=b.teacher_id where subject_id="+i_str+";";
            sqlite3_prepare( db, &select_stmt[0] , -1, &stmt, NULL );
            sqlite3_step( stmt );
            while( sqlite3_column_text( stmt, 0 ) ) {
                string t_name = string( (char *)sqlite3_column_text( stmt, 0 ));
                int t_count = atoi((char*)sqlite3_column_text( stmt, 1 ));
                teachers_name[i].push_back(t_name);
                teachers_count[i].push_back( t_count );
                sqlite3_step( stmt );
            }
        } else {
            qDebug() << "Failed to open db\n";
            return false;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    timetable se;
    cout<<"Setting variables\n";
    for(int i=1;i<6;i++) {
        if(!se.set_teachers_lab(i,teachers_count[i],teachers_name[i])) {
            cout<<"Unknown error\n";
            return false;
        }
    }

    vector <int> t1;
    vector <string> t2;


    for(int i=6;i<=14;i++) {
        t1.clear();
        t2.clear();
        sqlite3 *db;
        sqlite3_stmt * stmt;
        if (sqlite3_open("../timetable.db", &db) == SQLITE_OK) {
            char i_buf[1024];
            sprintf(i_buf,"%d",i);
            string i_str(i_buf);
            string select_stmt = "select a.name,b.load from assignment b inner join teacher a on a.teacher_id=b.teacher_id where subject_id="+i_str+";";
            sqlite3_prepare( db, &select_stmt[0] , -1, &stmt, NULL );
            sqlite3_step( stmt );
            while( sqlite3_column_text( stmt, 0 ) ) {
                string t_name = string( (char *)sqlite3_column_text( stmt, 0 ));
                int t_count = atoi((char*)sqlite3_column_text( stmt, 1 ));
                t2.push_back(t_name);
                t1.push_back( t_count );
                se.set_teachers_lec(i,t1,t2);
                sqlite3_step( stmt );
            }
        } else {
            qDebug() << "Failed to open db\n";
            return false;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);

    }

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
        return false;
    }


    ui->statusBar->showMessage("Timetable generated.");



    //Set lectures
    int count = 1;
    for(int i=0;i<4;i++)
    {
        mTemplate.clear();
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<7;k++)
            {
                QString str = "b" + QString::number(count++);

                //Divisions 1-3
                if(i<3)
                {
                    if(i==0&&j==5&&k==6)
                    {
                        qDebug()<<"lol";
                        //lol


                    }
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
                            mTemplate[str] = html == "         " || html == ""?html:html + "*";

                        }
                    }
                }
                else       //Special case for division 4
                {
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

                        if(k>0)
                        {
                            QString html = QString(se.get_batch_timetable(i*4,j,k).c_str()) + QString("<br><br><hr/>") + QString(se.get_batch_timetable(i*4,j,k+1).c_str());
                            mTemplate[str] = html;
                            k++;
                        }
                        else if(k==0)
                        {
                            QString html = QString(se.get_batch_timetable(i*4,j,k).c_str());
                            mTemplate[str] = html == "         " || html == ""?html:html + "*";
                        }
                    }
                }
            }
        }



        count = 1;
        //Set class room
        if(i<3)
            mTemplate["cl_room"] = se.get_class_room(i,1,1).c_str();

        //Set lab teacher names
        for(int p=0;p<4;p++)
        {
            for(int q=1;q<=5;q++)
            {

                int x = (i*4) + (p);
                if(x==16)
                {
                    x=15;
                    q=5;

                }
                QString str = "s" + QString::number(q) + QString::number(p+1);
                qDebug()<<str;
                mTemplate[str] = se.get_batch_lab_teacher(x ,q).c_str();
                //qDebug()<<se.get_batch_lab_teacher(x,p).c_str();
                str = "l" + QString::number(q) + QString::number(p+1);
                mTemplate[str] = se.get_batch_lab_name(x,q).c_str();
            }
        }

        //Set lecture subject teacher names
        for(int p=6;p<15;p++)
        {
            QString str = "t" + QString::number(p-5);
            mTemplate[str] = se.get_class_lec_teacher(i,p).c_str();
        }

        //Create HTML output
        convert(i+1);
    }
    display(current_div);
    ui->NextButton->show();
    ui->PrintButton->show();
    ui->PrevButton->show();

    return true;
}

void MainWindow::convert(int div)
{


    QString html;
    mTemplate["div"] = QString::number(div);
    mTemplate["year"] = "2014-15";
    mTemplate["sdate"] = "16-6-14";
    if(div!=4)
        html = mTemplate.expandFile(":/SE-I.html");
    else
        html = mTemplate.expandFile(":/SE-IV.html");
    QTextDocument document(html);
    QTextDocumentWriter writer("intermediate_data(division " + QString::number(div) + ").html");
    writer.setFormat("plaintext");
    writer.write(&document);



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
    printer.setPageSize(QPrinter::A4);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));

    if (dialog->exec() != QDialog::Accepted)
        return;


    ui->mWeb->print(&printer);
}
