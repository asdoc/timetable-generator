#include <QtGui/QApplication>
#include "mainwindow.h"
#include "timetableform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeTableForm w;
    w.setWindowTitle("Time Table generator");
    w.show();
    
    return a.exec();
}
