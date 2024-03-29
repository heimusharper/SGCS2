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
    Q_PROPERTY(QVariantList mapPath READ mapPath NOTIFY mapPathChanged)

public:
    enum ItemRole {
        TypeRole = Qt::UserRole + 1,
        param1 = TypeRole + 1,
        param2 = param1 + 1,
        param3 = param2 + 1,
        param4 = param3 + 1,
        param5 = param4 + 1,
        param6 = param5 + 1,
        param7 = param6 + 1,
        Pos = param7 + 1,
        PosFrame = Pos + 1,
        operation = PosFrame + 1
        };

    enum class ItemType : int
    {
        HOME = (int)MissionItem::ItemType::HOME,
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
        FRAME_RELATIVE = (int)MissionItem::Frame::FRAME_RELATIVE,
        FRAME_RELIEF = (int)MissionItem::Frame::FRAME_RELIEF,
        FRAME_ABSOLUTE = (int)MissionItem::Frame::FRAME_ABSOLUTE,
        FRAME_INVALID = (int)MissionItem::Frame::FRAME_INVALID
    };
    Q_ENUM(Frame)

    Mission(QObject *parent = nullptr);
    explicit Mission(DataStreamer *streamer, QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    Q_INVOKABLE void appendSimplePoint(const QGeoCoordinate &pos);
    Q_INVOKABLE void appendOperationAt(int at, int type, float p1, float p2, float p3,
                                       float p4, float p5, float p6, float p7, int frame);


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

    const QVariantList &mapPath() const;
    void setMapPath(const QVariantList &newMapPath);

    bool isEmpty() const;

public slots:
    void setHome(const QGeoCoordinate &newHome);

private slots:
    void appendPoint(const MissionItem &it);
    void replacePoint(int index, const MissionItem &it);

    void progressRead(float p, bool err);
    void progressWrite(float p, bool err);
    void setWriteErrorState(bool newWriteErrorState);
    void setReadErrorState(bool newReadErrorState);
    void setLastError(const QString &newLastError);

    void updateTrack();
private:

    DataStreamer *m_streamer = nullptr;

    QList<MissionItem> m_items;

    int m_defaultAltitude = 100;

    int m_defaultFrame = (int)MissionItem::Frame::FRAME_RELATIVE;

    bool m_writeErrorState = false;

    bool m_readErrorState = false;

    QString m_lastError;

    QVariantList m_mapPath;

    QGeoCoordinate m_home;

signals:

    void progress(float p);

    void defaultAltitudeChanged();
    void defaultFrameChanged();
    void writeErrorStateChanged();
    void readErrorStateChanged();
    void lastErrorChanged();
    void mapPathChanged();
};

#endif // MISSION_H
