#include "paintitem.h"



PaintItem::PaintItem(QQuickItem *parent):  QQuickPaintedItem(parent)
{
    imageToSend = new QImage(200,200,QImage::Format_RGB32);
    imageToSend->fill(QColor("black"));
}

void PaintItem::streamVideo(VideoStreamer *streamerThreadSlot)
{
    connect(streamerThreadSlot, SIGNAL(emitQImage(const QImage&)), this, SLOT(updateImage(const QImage&)));

}
void PaintItem::paint(QPainter *painter){
    painter->drawImage(this->boundingRect(), *imageToSend);
}

void PaintItem::updateImage(const QImage& image)
{
    *imageToSend = image;
    update();
}
