#ifndef UAV_H
#define UAV_H

#include <QObject>
#include "../streamer/DataStreamer.h"

class UAV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate homePosition READ homePosition WRITE setHomePosition NOTIFY homePositionChanged)

public:
    explicit UAV(DataStreamer *streamer, QObject *parent = nullptr);

    const QGeoCoordinate &homePosition() const;
    void setHomePosition(const QGeoCoordinate &newHomePosition);

public slots:

    Q_INVOKABLE void doRequestHomePosition();

private:

    DataStreamer *m_streamer = nullptr;

    QGeoCoordinate m_homePosition;

signals:

    void homePositionChanged();
};

#endif // UAV_H
