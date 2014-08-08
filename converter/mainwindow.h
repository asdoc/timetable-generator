#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWebView>
#include <QUrl>
#include <QCTemplate.h>


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
    QWebView *mWeb;
    QCTemplate mTemplate;
private slots:
    void convert();
    void print();
};

#endif // MAINWINDOW_H
