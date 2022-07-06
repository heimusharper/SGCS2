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
    if (m_items.size() <= index)
        return nullptr;
    return m_items.at(index);
}

void Mission::appendSimplePoint(const QGeoCoordinate &pos)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    MissionItem *item = new MissionItem;
    item->setType((int)MissionItem::ItemType::SIMPLE_POINT);
    item->setPosition(pos);
    item->setDelayOnWaypoint(-1);
    item->setFrame((int)m_lastFrame);
    m_items.push_back(item);
    initItem(item);
    endInsertRows();
}

void Mission::setSimplePoint(int index, const QGeoCoordinate &pos, int wait, int frame)
{
    if (index >= m_items.size()) {
        appendSimplePoint(pos);
        setSimplePoint(index, pos, wait, frame);
    } else {
        auto obj = m_items.at(index);
        obj->setPosition(pos);
        obj->setDelayOnWaypoint(wait);
        obj->setFrame(frame);
        m_lastFrame = (MissionItem::Frame)frame;
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
        connect(request, &MissionReadRequest::onItem, this, [this](int index, MissionItem *it) {
            if (index == 0)
                clear();
            replacePoint(index, it);
        });
        connect(request, &MissionReadRequest::progress, this, &Mission::progress);
    }
}

void Mission::writeAll()
{

}

void Mission::clear()
{
    if (m_items.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_items.size());
    while (!m_items.empty())
    {
        m_items.takeFirst()->deleteLater();
    }
    endRemoveRows();
}

void Mission::appendPoint(MissionItem *it)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(it);
    initItem(it);
    endInsertRows();
}

void Mission::replacePoint(int index, MissionItem *it)
{
    if (index >= m_items.size())
        appendPoint(it);
    else {
        auto obj = m_items.at(index);
        m_items.replace(index, it);
        initItem(it);
        obj->deleteLater();
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged( topLeft, bottomRight );
    }
}

void Mission::initItem(MissionItem *it)
{
    auto changes = [this, it](){
        int index = m_items.indexOf(it);
        if (index >= 0) {
            QModelIndex topLeft = createIndex(index, 0);
            QModelIndex bottomRight = createIndex(index, 0);
            emit dataChanged(topLeft, bottomRight);
            qDebug() << "on update " << index;
        }
    };
    connect(it, &MissionItem::typeChanged, this, changes);
    connect(it, &MissionItem::positionChanged, this, changes);
    connect(it, &MissionItem::delayOnWaypointChanged, this, changes);
    connect(it, &MissionItem::jumpToChanged, this, changes);
    connect(it, &MissionItem::jumpRepeatsChanged, this, changes);
    connect(it, &MissionItem::distanceChanged, this, changes);
    connect(it, &MissionItem::speedChanged, this, changes);
    connect(it, &MissionItem::servoChanged, this, changes);
    connect(it, &MissionItem::pwmChanged, this, changes);
    connect(it, &MissionItem::zoomPositionChanged, this, changes);
    connect(it, &MissionItem::autofocusNowChanged, this, changes);
    connect(it, &MissionItem::shootChanged, this, changes);
    connect(it, &MissionItem::recordStartChanged, this, changes);
    connect(it, &MissionItem::gimbalPitchChanged, this, changes);
    connect(it, &MissionItem::gimbalRollChanged, this, changes);
    connect(it, &MissionItem::gimbalYawChanged, this, changes);
    connect(it, &MissionItem::shootOnTimeChanged, this, changes);
    connect(it, &MissionItem::shootOnDistanceChanged, this, changes);
    connect(it, &MissionItem::frameChanged, this, changes);
}

