#include "teacherdialog.h"
#include "ui_teacherdialog.h"

TeacherDialog::TeacherDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::TeacherDialog),
    db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);
    this->setWindowTitle("Add/Edit teacher");
    this->setFixedSize(this->width(), this->height());
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_2->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);

    proxy = new QSortFilterProxyModel;
    load_proxy = new QSortFilterProxyModel;

    //set up the database
    db.setDatabaseName("../timetable.db");
    db.open();
    teacher_model = new QSqlRelationalTableModel(this, db);
    load_teachers();
    assignment_model = new QSqlRelationalTableModel(this,db);
    load_teacher_assignment();
    connect(ui->add_button, SIGNAL(clicked()), this, SLOT(add_new_teacher()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(button_clicked(QAbstractButton*)));
    connect(ui->delete_teacher_button, SIGNAL(clicked()), this, SLOT(delete_teacher()));
    connect(ui->delete_load_button, SIGNAL(clicked()), this, SLOT(delete_load()));
    connect(ui->add_load_button, SIGNAL(clicked()), this, SLOT(add_new_load()));
    connect(ui->filter_lbl, SIGNAL(textChanged(QString)), this, SLOT(filter(QString)));
}

TeacherDialog::~TeacherDialog()
{
    delete ui;
}

void TeacherDialog::load_teachers()
{



    teacher_model->setTable("teacher");
    teacher_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    teacher_model->setRelation(1, QSqlRelation("department","department_id","name"));
    teacher_model->setHeaderData(0,Qt::Horizontal, tr("Teacher ID"));
    teacher_model->setHeaderData(1,Qt::Horizontal, tr("Department ID"));
    teacher_model->setHeaderData(2,Qt::Horizontal, tr("Teacher Name"));
    teacher_model->select();


    ui->tableView->setModel(teacher_model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}

void TeacherDialog::load_teacher_assignment()
{
    assignment_model->setTable("assignment");
    assignment_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    assignment_model->setRelation(1, QSqlRelation("teacher", "teacher_id", "name"));
    assignment_model->setRelation(2, QSqlRelation("subject", "subject_id", "name"));
    assignment_model->setHeaderData(0,Qt::Horizontal, tr("Assignment ID"));
    assignment_model->setHeaderData(1,Qt::Horizontal, tr("Teacher"));
    assignment_model->setHeaderData(2,Qt::Horizontal, tr("Subject"));
    assignment_model->setHeaderData(3,Qt::Horizontal, tr("Load (in hours)"));
    assignment_model->select();
    ui->tableView_2->setModel(assignment_model);
    ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
}

void TeacherDialog::button_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton b = ui->buttonBox->standardButton(button);
    switch(b)
    {
        case QDialogButtonBox::Apply:
            teacher_model->submitAll();
            assignment_model->submitAll();
            QMessageBox::information(this,"Saved","Changes have been successfully saved.");
            break;
        default:
            break;
    }
}

void TeacherDialog::delete_teacher()
{
    int row_number = ui->tableView->currentIndex().row();
    ui->tableView->model()->removeRow(row_number);
    QString name = ui->tableView_2->model()->index(row_number,1).data().toString();
    for(int i=0;i<ui->tableView_2->model()->rowCount();i++)
    {
        QString sname = ui->tableView_2->model()->index(i,1).data().toString();
        if( name == sname )
        {
            ui->tableView_2->model()->removeRow(i);
            qDebug()<<"lol";
        }
    }
}

void TeacherDialog::delete_load()
{
    int row_number = ui->tableView_2->currentIndex().row();
    ui->tableView_2->model()->removeRow(row_number);
}


void TeacherDialog::add_new_teacher()
{
    QString name = ui->name_input->text();
    int branch = ui->branch_combo->currentIndex();
    if(branch==0 || ui->name_input->text().isEmpty()) return;

    db.exec("insert into teacher values(NULL, " + QString::number(branch) + ", '" + name + "')");
    teacher_model->select();
    qDebug()<< db.lastError();
}


void TeacherDialog::add_new_load()
{
    int row = ui->tableView_2->model()->rowCount();
    ui->tableView_2->model()->insertRow(row);
    ui->tableView_2->scrollToBottom();
}

void TeacherDialog::filter(QString pat)
{
    QString pattern = "*" + pat + "*";
    proxy->setSourceModel(teacher_model);
    proxy->setFilterKeyColumn(2);
    proxy->setFilterWildcard(pattern);
    ui->tableView->setModel(proxy);

    load_proxy->setSourceModel(assignment_model);
    load_proxy->setFilterKeyColumn(1);
    load_proxy->setFilterWildcard(pattern);
    ui->tableView_2->setModel(load_proxy);

}
