#ifndef PHOTOPAYLOAD_H
#define PHOTOPAYLOAD_H

#include <QObject>
#include "../streamer/DataStreamer.h"
#include <QAbstractListModel>
#include <QDebug>

class PhotoPayload : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(float onTime READ onTime WRITE setOnTime NOTIFY onTimeChanged)
    Q_PROPERTY(float onDistance READ onDistance WRITE setOnDistance NOTIFY onDistanceChanged)
    Q_PROPERTY(int fullCount READ fullCount WRITE setFullCount NOTIFY fullCountChanged)
    Q_PROPERTY(int fullCountSecond READ fullCountSecond WRITE setFullCountSecond NOTIFY fullCountSecondChanged)

public:
    enum ItemRole {
        Latitude = Qt::UserRole + 1,
        Longitude = Latitude + 1,
        Altitude = Longitude + 1
        };
    PhotoPayload(QObject *parent = nullptr);
    explicit PhotoPayload(DataStreamer *streamer, QObject *parent = nullptr);

    Q_INVOKABLE void commit(float time, float dst);
    Q_INVOKABLE void takeShot();

    int rowCount(const QModelIndex&) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    float onTime() const;
    void setOnTime(float newOnTime);

    float onDistance() const;
    void setOnDistance(float newOnDistance);

    int fullCount() const;
    void setFullCount(int newFullCount);

    int fullCountSecond() const;
    void setFullCountSecond(int newFullCount);

signals:

    void onTimeChanged();

    void onDistanceChanged();

    void fullCountChanged();

    void fullCountSecondChanged();

private:

    struct Photo
    {
        Photo(const QGeoCoordinate &c) : pos(c) {}
        QGeoCoordinate pos;
    };

    QList<Photo> m_photos;

    DataStreamer *m_streamer = nullptr;

    float m_onTime = 0;
    float m_onDistance = 0;
    int m_fullCount = 0;
    int m_fullCountSecond = 0;
};

#endif // PHOTOPAYLOAD_H
