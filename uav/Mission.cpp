#include "Mission.h"

Mission::Mission(QObject *parent)
    : QAbstractListModel{parent}
{

}

Mission::Mission(DataStreamer *streamer, QObject *parent)
    : QAbstractListModel{parent},
    m_streamer(streamer)
{

}

int Mission::rowCount(const QModelIndex &) const
{
    return m_items.size();
}

QHash<int, QByteArray> Mission::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[Latitude] = "lat";
    roles[Longitude] = "lon";
    roles[Altitude] = "alt";

    return roles;
}

QVariant Mission::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TypeRole:
        return m_items.at(index.row())->type();
    case Latitude:
        return m_items.at(index.row())->position().latitude();
    case Longitude:
        return m_items.at(index.row())->position().longitude();
    case Altitude:
        return m_items.at(index.row())->position().altitude();
    default:
        break;
    }
    return QVariant();
}

MissionItem *Mission::itemAt(int index)
{
    return m_items.at(index);
}

void Mission::appendSimplePoint(const QGeoCoordinate &pos)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    MissionItem *item = new MissionItem;
    item->setPosition(pos);
    m_items.push_back(item);
    endInsertRows();
}

void Mission::setSimplePoint(int index, const QGeoCoordinate &pos)
{
    if (index >= m_items.size())
        appendSimplePoint(pos);
    else {
        auto obj = m_items.at(index);
        obj->setPosition(pos);
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged( topLeft, bottomRight );
    }
}

void Mission::removeOne(int index)
{
    if (index < m_items.size()) {
        beginRemoveRows(QModelIndex(), index, index);
        m_items.takeAt(index)->deleteLater();
        endRemoveRows();
    }
}

void Mission::readAll()
{
    if (m_streamer)
    {
        auto request = m_streamer->createMissionReadRequest();
        /* connect(request, &MissionReadRequest::onError, this, [this](MissionReadRequest::Errors err){

        });*/
        connect(request, &MissionReadRequest::onItem, this, [this](uint16_t seq, MissionReadRequest::PointType type, float p1, float p2, float p3, float p4, double x, double y, double z){
            switch (type) {
            case MissionReadRequest::PointType::SIMPLE_POINT:
                setSimplePoint(seq, QGeoCoordinate(x, y, z));
                break;
            default:
                break;
            }
        });
        connect(request, &MissionReadRequest::progress, this, &Mission::progress);
    }
}

int MissionItem::type() const
{
    return m_type;
}

void MissionItem::setType(int newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

const QGeoCoordinate &MissionItem::position() const
{
    return m_position;
}

void MissionItem::setPosition(const QGeoCoordinate &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}
