#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWebView>
#include <QUrl>
#include <QCTemplate.h>
#include <vector>
#include "../timetable.h"

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QCTemplate mTemplate;
    int current_div;
    void display(int);
public slots:
    void convert(int div);
    void generate();
    void print();
    void next();
    void prev();
};

#endif // MAINWINDOW_H
