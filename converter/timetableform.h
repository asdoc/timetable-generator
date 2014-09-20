#ifndef TIMETABLEFORM_H
#define TIMETABLEFORM_H

#include <QMainWindow>
#include "mainwindow.h"
#include "teacherdialog.h"

class MainWindow;
namespace Ui {
class TimeTableForm;
}

class TimeTableForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TimeTableForm(QWidget *parent = 0);
    MainWindow *mMainWindow;
    ~TimeTableForm();
    
private:
    Ui::TimeTableForm *ui;
    TeacherDialog *dialog;

private slots:
    void open_main_window();
    void open_input_window();
};

#endif // TIMETABLEFORM_H
