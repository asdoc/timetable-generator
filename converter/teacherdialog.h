#ifndef TEACHERDIALOG_H
#define TEACHERDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtSql/QtSql>
using namespace std;

namespace Ui {
class TeacherDialog;
}

class TeacherDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TeacherDialog(QWidget *parent = 0);
    ~TeacherDialog();
    
private:
    Ui::TeacherDialog *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel *teacher_model;
    QSqlRelationalTableModel *assignment_model;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *load_proxy;

private slots:
    void add_new_teacher();
    void add_new_load();
    void button_clicked(QAbstractButton *);
    void load_teachers();
    void load_teacher_assignment();
    void delete_row();
    void filter(QString);
};

#endif // TEACHERDIALOG_H
