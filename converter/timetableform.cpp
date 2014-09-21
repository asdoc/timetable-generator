#include "timetableform.h"
#include "ui_timetableform.h"

TimeTableForm::TimeTableForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeTableForm)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Select an option to continue.");
    dialog = 0;
    mMainWindow = 0;
    connect(ui->ExitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->LoadButton, SIGNAL(clicked()), this, SLOT(open_main_window()));
    connect(ui->AddTeacherButton, SIGNAL(clicked()), this, SLOT(open_input_window()));
}

void TimeTableForm::open_main_window()
{

    mMainWindow = new MainWindow();
    mMainWindow->setWindowTitle("Timetable Generator");
    mMainWindow->show();
    this->close();
}

void TimeTableForm::open_input_window()
{

    dialog = new TeacherDialog(this);
    dialog->setModal(true);
    dialog->show();

}

TimeTableForm::~TimeTableForm()
{
    delete ui;
}
