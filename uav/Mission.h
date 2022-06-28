#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QGeoCoordinate>
#include "../streamer/DataStreamer.h"

class MissionItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
public:
    enum ItemType
    {
        SimpleType
    };
    Q_ENUMS(ItemType)

    int type() const;
    void setType(int newType);

    const QGeoCoordinate &position() const;
    void setPosition(const QGeoCoordinate &newPosition);

signals:
    void typeChanged();

    void positionChanged();

private:
    int m_type;
    QGeoCoordinate m_position;
};

class Mission : public QAbstractListModel
{
    Q_OBJECT
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
    Q_INVOKABLE void setSimplePoint(int index, const QGeoCoordinate &pos);
    Q_INVOKABLE void removeOne(int index);

    Q_INVOKABLE void readAll();

private:

    DataStreamer *m_streamer = nullptr;

    QList<MissionItem*> m_items;

signals:

    void progress(float p);

};

#endif // MISSION_H
