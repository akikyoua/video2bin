#include "mythread.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

using namespace cv;

MyThread::MyThread(QObject *parent)
{

}

MyThread::~MyThread()
{
    QThread::destroyed();
    this->exit();
}


void MyThread::run()
{
    //指定文件
    QFile file;
    QDataStream stream;
    //file.setFileName(ui->ledtClose->text());
    file.setFileName(saveFileName);
    //打开文件，指定打开方式
    file.open(QIODevice::ReadWrite);
    stream.setDevice(&file);
    //获取textEdit的内容
    uint8_t byteData[1600];

    //打开视频文件：其实就是建立一个VideoCapture结构
    //qDebug() << "filename=" << openFileName;
    capture = VideoCapture(openFileName.toStdString());
    //检测是否正常打开:成功打开时，isOpened返回ture
    if(!capture.isOpened())
        qDebug()<<"fail to open!";
    //获取整个帧数
    long totalFrameNumber = (long)capture.get(CAP_PROP_FRAME_COUNT);
    qDebug()<<"total frame"<<QString::number(totalFrameNumber)<<"帧";
    //设置开始帧()
    long frameCurrent = 0;
    capture.set( CAP_PROP_POS_FRAMES,frameCurrent);

    //获取帧率
    //double rate = capture.get(CAP_PROP_FPS);
    //qDebug()<<"frame rate:"<<QString::number(rate)<<endl;
    //for(frameCurrent = 0;frameCurrent<totalFrameNumber;frameCurrent++)
    Mat currentFrame;
    while(1)
    {
        if(!capture.read(currentFrame))
        {
            qDebug()<<"读取视频失败"<<endl;
            //关闭视频文件
            capture.release();
            //关闭文件，关闭后才真正写进去
            file.close();
            break;
        }
        else
        {
            resize(currentFrame, frame, Size(160, 80), 0, 0, INTER_NEAREST );
            cvtColor(frame, frame, CV_BGR2GRAY);
            //threshold(frame, frame, 125, 255, THRESH_BINARY);
            //获取像素点内容填充至数组
            for (int j=0; j<80; j++)
            {
                uchar* pdata= frame.ptr<uchar>(j);
                for (int i=0; i<20; i++)
                {
                    byteData[20*j+i] = 0x00;
                    int mask = 0x80;
                    for(int n = 0; n < 8; n++)
                    {
                        if(!pdata[i*8+n])
                        {
                            byteData[20*j+i] |= mask;
                        }
                        mask >>= 1;
                    }
                }
            }
            //写入文件流
            stream.writeRawData((const char *)byteData,1600);
            frameCurrent++;
            progess = frameCurrent*100/totalFrameNumber;
            emit Send2UI();
        }
    }
}

void MyThread::setOpenFileName(QString str)
{
    openFileName = str;
}

void MyThread::setSaveFileName(QString str)
{
    saveFileName = str;
}
