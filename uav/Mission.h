#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QGeoCoordinate>
#include <QDebug>
#include "../streamer/DataStreamer.h"
#include "MissionItem.h"


class Mission : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int defaultAltitude READ defaultAltitude WRITE setDefaultAltitude NOTIFY defaultAltitudeChanged)
    Q_PROPERTY(int defaultFrame READ defaultFrame WRITE setDefaultFrame NOTIFY defaultFrameChanged)
    Q_PROPERTY(bool writeErrorState READ writeErrorState NOTIFY writeErrorStateChanged)
    Q_PROPERTY(bool readErrorState READ readErrorState NOTIFY readErrorStateChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
public:
    enum ItemRole {
        TypeRole = Qt::UserRole + 1,
        param1 = TypeRole + 1,
        param2 = param1 + 1,
        param3 = param2 + 1,
        param4 = param3 + 1,
        Latitude = param4 + 1,
        Longitude = Latitude + 1,
        Altitude = Longitude + 1,
        PosFrame = Altitude + 1
        };

    enum class ItemType : int
    {
        SIMPLE_POINT = (int)MissionItem::ItemType::SIMPLE_POINT,
        TAKEOFF = (int)MissionItem::ItemType::TAKEOFF,
        RTL = (int)MissionItem::ItemType::RTL,
        LAND = (int)MissionItem::ItemType::LAND,
        JUMP = (int)MissionItem::ItemType::JUMP,
        DELAY = (int)MissionItem::ItemType::DELAY,
        DISTANCE = (int)MissionItem::ItemType::DISTANCE,
        SPEED = (int)MissionItem::ItemType::SPEED,
        SET_SERVO = (int)MissionItem::ItemType::SET_SERVO,
        ROI = (int)MissionItem::ItemType::ROI,
        CAMERA = (int)MissionItem::ItemType::CAMERA,
        GIMBAL = (int)MissionItem::ItemType::GIMBAL,
        TRIGGER = (int)MissionItem::ItemType::TRIGGER,
        PARACHUTE = (int)MissionItem::ItemType::PARACHUTE
    };
    Q_ENUM(ItemType)
    enum class Frame : int
    {
        RELATIVE = (int)MissionItem::Frame::RELATIVE,
        RELIEF = (int)MissionItem::Frame::RELIEF,
        ABSOLUTE = (int)MissionItem::Frame::ABSOLUTE,
        INVALID = (int)MissionItem::Frame::INVALID
    };
    Q_ENUM(Frame)

    Mission(QObject *parent = nullptr);
    explicit Mission(DataStreamer *streamer, QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

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

    bool writeErrorState() const;

    bool readErrorState() const;

    const QString &lastError() const;

private slots:
    void appendPoint(const MissionItem &it);
    void replacePoint(int index, const MissionItem &it);

    void progressRead(float p, bool err);
    void progressWrite(float p, bool err);
    void setWriteErrorState(bool newWriteErrorState);
    void setReadErrorState(bool newReadErrorState);
    void setLastError(const QString &newLastError);
private:

    DataStreamer *m_streamer = nullptr;

    QList<MissionItem> m_items;

    int m_defaultAltitude = 100;

    int m_defaultFrame = (int)MissionItem::Frame::RELATIVE;

    bool m_writeErrorState = false;

    bool m_readErrorState = false;

    QString m_lastError;

signals:

    void progress(float p);

    void defaultAltitudeChanged();
    void defaultFrameChanged();
    void writeErrorStateChanged();
    void readErrorStateChanged();
    void lastErrorChanged();
};

#endif // MISSION_H
