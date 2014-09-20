#ifndef TEACHERDIALOG_H
#define TEACHERDIALOG_H

#include <QDialog>
#include <QtGui>

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
    vector<QGroupBox *> boxes;

private slots:
    void add_new_teacher();
};

#endif // TEACHERDIALOG_H
