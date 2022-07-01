#ifndef PHOTOPAYLOADSTREAM_H
#define PHOTOPAYLOADSTREAM_H

#include <QObject>
#include <QGeoCoordinate>

class PhotoPayloadStream : public QObject
{
    Q_OBJECT
public:
    explicit PhotoPayloadStream(QObject *parent = nullptr) : QObject(parent)
    {
    }
    virtual ~PhotoPayloadStream() = default;

    virtual void takeOneShot() = 0;

signals:
    void onTakeShot(int index, const QGeoCoordinate &pos);
};

#endif // PHOTOPAYLOADSTREAM_H
