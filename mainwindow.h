#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mythread.h"

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MyThread *mythread;

private slots:

    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnStart_clicked();
    void updateConvert();

};
#endif // MAINWINDOW_H
