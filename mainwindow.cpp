#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mythread = new MyThread(this);
    connect(mythread, SIGNAL(Send2UI()), this, SLOT(updateConvert()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateConvert()
{
    ui->labdispaly->setPixmap(QPixmap::fromImage(QImage(mythread->frame.data, mythread->frame.cols, mythread->frame.rows, mythread->frame.step, QImage::Format_Grayscale8)));
    ui->progressBar->setValue(mythread->progess);
}

void MainWindow::on_btnOpen_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle = "OpenFile"; //对话框标题
    QString filter = "ChoseFile(*.*)"; //文件过滤器
    QString openFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (openFileName.isEmpty())
        return;
    else
    {
        ui->ledtOpen->setText(openFileName);
        mythread->setOpenFileName(openFileName);
    }

}

void MainWindow::on_btnSave_clicked()
{
    QString curPath=QDir::currentPath();
    QString saveFileName = QFileDialog::getSaveFileName(this,tr("SaveFile"),curPath,
                 "fileName(*.bin)");
    if (saveFileName.isEmpty())
        return;
    else
    {
        ui->ledtSave->setText(saveFileName);
        mythread->setSaveFileName(saveFileName);
    }
}

void MainWindow::on_btnStart_clicked()
{
    mythread->start();
}

