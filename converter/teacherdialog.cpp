#include "teacherdialog.h"
#include "ui_teacherdialog.h"

TeacherDialog::TeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherDialog)
{
    ui->setupUi(this);
}

TeacherDialog::~TeacherDialog()
{
    delete ui;
}

void TeacherDialog::add_new_teacher()
{

}
