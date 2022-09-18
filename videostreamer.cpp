#include "videostreamer.h"

VideoStreamer::VideoStreamer()
{

}

VideoStreamer::~VideoStreamer()
{
    cap.release();
    tUpdate.stop();
    threadStreamer->requestInterruption();
}



void VideoStreamer::catchFrame(cv::Mat emittedFrame)
{

    QImage imgIn= QImage((uchar*) emittedFrame.data, emittedFrame.cols, emittedFrame.rows, emittedFrame.step, QImage::Format_RGB888).rgbSwapped();

    emit emitQImage(imgIn);

}

void VideoStreamer::openVideoCamera(QString path)
{
    if(path.length() == 1)
    cap.open(path.toInt());
    else
    cap.open(path.toStdString());





    VideoStreamer* worker = new VideoStreamer();
    worker->moveToThread(threadStreamer);
    QObject::connect(threadStreamer,SIGNAL(started()),worker,SLOT(streamerThreadSlot()));
    QObject::connect(worker,&VideoStreamer::emitThreadImage,this,&VideoStreamer::catchFrame);
    threadStreamer->start();


}

void VideoStreamer::streamerThreadSlot()
{
    cv::Mat tempFrame;


    while (1) {
        cap>>tempFrame;

        if(tempFrame.data)
        {
           emit emitThreadImage(tempFrame);

        }

        if(QThread::currentThread()->isInterruptionRequested())
        {
            cap.release();
            return;
        }

    }
}
