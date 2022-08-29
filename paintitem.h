#ifndef PAINTITEM_H
#define PAINTITEM_H

#include <QObject>
#include <QtQuick>
#include <QImage>

#include <videostreamer.h>

class PaintItem: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(VideoStreamer* streamerThreadSlot WRITE streamVideo)

public:
    PaintItem(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
    void streamVideo(VideoStreamer* streamerThreadSlot);

public slots:
    void updateImage(const QImage&);

protected:
    QImage *imageToSend;


};

#endif // PAINTITEM_H
