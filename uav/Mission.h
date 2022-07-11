#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QGeoCoordinate>
#include "MissionItem.h"
#include <QDebug>
#include "../streamer/DataStreamer.h"

class Mission : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int defaultAltitude READ defaultAltitude WRITE setDefaultAltitude NOTIFY defaultAltitudeChanged)
    Q_PROPERTY(int defaultFrame READ defaultFrame WRITE setDefaultFrame NOTIFY defaultFrameChanged)
public:
    enum ItemRole {
        TypeRole = Qt::UserRole + 1,
        Latitude = TypeRole + 1,
        Longitude = Latitude + 1,
        Altitude = Longitude + 1
        };

    Mission(QObject *parent = nullptr);
    explicit Mission(DataStreamer *streamer, QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;
    Q_INVOKABLE MissionItem *itemAt(int index);

    Q_INVOKABLE void appendSimplePoint(const QGeoCoordinate &pos);
    Q_INVOKABLE void setSimplePoint(int index, const QGeoCoordinate &pos, int wait, int frame);
    Q_INVOKABLE void removeOne(int index);
    Q_INVOKABLE void readAll();
    Q_INVOKABLE void writeAll();
    Q_INVOKABLE void clear();

    int defaultAltitude() const;
    void setDefaultAltitude(int newDefaultAltitude);

    int defaultFrame() const;
    void setDefaultFrame(int newDefaultFrame);

private slots:
    void appendPoint(MissionItem *it);
    void replacePoint(int index, MissionItem *it);
    void initItem(MissionItem *it);
private:

    DataStreamer *m_streamer = nullptr;

    QList<MissionItem*> m_items;

    int m_defaultAltitude = 100;

    int m_defaultFrame = (int)MissionItem::Frame::RELATIVE;

signals:

    void progress(float p);

    void defaultAltitudeChanged();
    void defaultFrameChanged();
};

#endif // MISSION_H
