#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(QObject *parent);
    ~MyThread();
    void run();

    void setOpenFileName(QString str);
    void setSaveFileName(QString str);

    cv::Mat frame;
    int progess;

private:

    QString openFileName;
    QString saveFileName;

    cv::VideoCapture capture;

signals:
    // 自定义信号
    void Send2UI();
};

#endif
