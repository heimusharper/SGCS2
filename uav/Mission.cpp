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
    roles[param1] = "param1";
    roles[param2] = "param2";
    roles[param3] = "param3";
    roles[param4] = "param4";
    roles[param5] = "param5";
    roles[param6] = "param6";
    roles[param7] = "param7";
    roles[Pos] = "pos";
    roles[PosFrame] = "frame";
    roles[operation] = "operation";
    return roles;
}

QVariant Mission::data(const QModelIndex &index, int role) const
{
    if (index.row() >= m_items.size())
        return QVariant();
    switch (role) {
    case TypeRole:
        return (int)m_items.at(index.row()).type;
    case param1:
        return m_items.at(index.row()).param_1;
    case param2:
        return m_items.at(index.row()).param_2;
    case param3:
        return m_items.at(index.row()).param_3;
    case param4:
        return m_items.at(index.row()).param_4;
    case param5:
        return m_items.at(index.row()).param_x;
    case param6:
        return m_items.at(index.row()).param_y;
    case param7:
        return m_items.at(index.row()).param_z;
    case Pos: {
        if (m_items.at(index.row()).type == MissionItem::ItemType::SIMPLE_POINT) {
            return QVariant::fromValue(QGeoCoordinate(m_items.at(index.row()).param_x,
                                                      m_items.at(index.row()).param_y,
                                                      m_items.at(index.row()).param_z));
        }else {
            for (int i = index.row(); i > 0 && i < m_items.size(); i++) {
                if (m_items.at(i).type == MissionItem::ItemType::SIMPLE_POINT) {
                    return QVariant::fromValue(QGeoCoordinate(m_items.at(i).param_x,
                                                              m_items.at(i).param_y,
                                                              m_items.at(i).param_z));
                }
            }
        }
        return QVariant::fromValue(m_home);
    }
    case PosFrame:
        return (int)m_items.at(index.row()).frame;
    case operation:
    {
        if (m_items.at(index.row()).type == MissionItem::ItemType::SIMPLE_POINT)
            return 0;
        else {
            int index_op = 0;
            for (int i = index.row(); i > 0 && i < m_items.size(); i++) {
                if (m_items.at(i).type != MissionItem::ItemType::SIMPLE_POINT)
                    index_op++;
                else
                    return index_op;
            }
        }
        return -1;
    }
    default:
        break;
    }
    return QVariant();
}

void Mission::appendSimplePoint(const QGeoCoordinate &pos)
{
    if (m_items.size() == 0)
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size() + 1);
        {
            MissionItem item;
            item.type = MissionItem::ItemType::TAKEOFF;
            item.param_x = 0;
            item.param_y = 0;
            item.param_z = pos.altitude();
            m_items.push_back(item);
        }
    } else
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    {
        MissionItem item;
        item.type = MissionItem::ItemType::SIMPLE_POINT;
        item.param_x = pos.latitude();
        item.param_y = pos.longitude();
        item.param_z = pos.altitude();
        item.param_1 = -1;
        item.frame = (MissionItem::Frame)m_defaultFrame;
        m_items.push_back(item);
    }
    endInsertRows();
    updateTrack();
}

void Mission::appendOperationAt(int at, int type, float p1, float p2, float p3, float p4, float p5, float p6, float p7, int frame)
{
    if (at < m_items.size()) {
        beginInsertRows(QModelIndex(), at, at);
        MissionItem item;
        item.type = (MissionItem::ItemType)type;
        item.frame = (MissionItem::Frame)frame;
        item.param_1 = p1;
        item.param_2 = p2;
        item.param_3 = p3;
        item.param_4 = p4;
        item.param_x = p5;
        item.param_y = p6;
        item.param_z = p7;
        m_items.insert(at + 1, item);
        endInsertRows();
    }
}

void Mission::setSimplePoint(int index, const QGeoCoordinate &pos, int wait, int frame)
{
    if (index >= m_items.size()) {
        appendSimplePoint(pos);
        setSimplePoint(index, pos, wait, frame);
    } else {
        auto obj = m_items.at(index);
        obj.param_x = pos.latitude();
        obj.param_y = pos.longitude();
        obj.param_z = pos.altitude();
        obj.param_1 = wait;
        obj.frame = (MissionItem::Frame)frame;
        m_items.replace(index, obj);
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged( topLeft, bottomRight );
        if (obj.type == MissionItem::ItemType::SIMPLE_POINT)
            updateTrack();
    }
}

void Mission::removeOne(int index)
{
    if (index < m_items.size()) {
        beginRemoveRows(QModelIndex(), index, index);
        auto it = m_items.takeAt(index);
        endRemoveRows();
        if (it.type == MissionItem::ItemType::SIMPLE_POINT)
            updateTrack();
    }
}

void Mission::readAll()
{
    if (m_streamer)
    {
        auto request = m_streamer->createMissionReadRequest();
        connect(request, &MissionReadRequest::onItem, this, [this](int index, const MissionItem &it) {
            if (index == 0)
                clear();
            replacePoint(index, it);
        });
        connect(request, &MissionReadRequest::progress, this, &Mission::progressRead);
        connect(request, &MissionReadRequest::onError, this, &Mission::setLastError);
    }
}

void Mission::writeAll()
{
    if (m_streamer)
    {
        auto request = m_streamer->createMissionWriteRequest();
        request->set(m_items);
        connect(request, &MissionWriteRequest::progress, this, &Mission::progressWrite);
        connect(request, &MissionWriteRequest::onError, this, &Mission::setLastError);
    }
}

void Mission::clear()
{
    if (m_items.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_items.size());
    m_items.clear();
    endRemoveRows();
    updateTrack();
}

void Mission::appendPoint(const MissionItem &it)
{
    if (m_items.size() == 0)
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size() + 1);
        {
            MissionItem item;
            item.type = MissionItem::ItemType::TAKEOFF;
            item.param_x = 0;
            item.param_y = 0;
            item.param_z = 0;
            m_items.push_back(item);
        }
    } else
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.push_back(it);
    endInsertRows();
    if (it.type == MissionItem::ItemType::SIMPLE_POINT)
        updateTrack();
}

void Mission::replacePoint(int index, const MissionItem &it)
{
    if (index >= m_items.size())
        appendPoint(it);
    else {
        m_items.replace(index, it);
        QModelIndex topLeft = createIndex(index, 0);
        QModelIndex bottomRight = createIndex(index, 0);
        emit dataChanged( topLeft, bottomRight );
        if (it.type == MissionItem::ItemType::SIMPLE_POINT)
            updateTrack();
    }
}

void Mission::progressRead(float p, bool err)
{
    emit progress(p);
    setReadErrorState(err);
}

void Mission::progressWrite(float p, bool err)
{
    emit progress(p);
    setWriteErrorState(err);
}


int Mission::defaultAltitude() const
{
    return m_defaultAltitude;
}

void Mission::setDefaultAltitude(int newDefaultAltitude)
{
    if (m_defaultAltitude == newDefaultAltitude)
        return;
    m_defaultAltitude = newDefaultAltitude;
    emit defaultAltitudeChanged();
}

int Mission::defaultFrame() const
{
    return m_defaultFrame;
}

void Mission::setDefaultFrame(int newDefaultFrame)
{
    if (m_defaultFrame == newDefaultFrame)
        return;
    m_defaultFrame = newDefaultFrame;
    emit defaultFrameChanged();
}

bool Mission::writeErrorState() const
{
    return m_writeErrorState;
}

void Mission::setWriteErrorState(bool newWriteErrorState)
{
    if (m_writeErrorState == newWriteErrorState)
        return;
    m_writeErrorState = newWriteErrorState;
    emit writeErrorStateChanged();
}

bool Mission::readErrorState() const
{
    return m_readErrorState;
}

void Mission::setReadErrorState(bool newReadErrorState)
{
    if (m_readErrorState == newReadErrorState)
        return;
    m_readErrorState = newReadErrorState;
    emit readErrorStateChanged();
}

const QString &Mission::lastError() const
{
    return m_lastError;
}

void Mission::setLastError(const QString &newLastError)
{
    if (m_lastError == newLastError)
        return;
    m_lastError = newLastError;
    emit lastErrorChanged();
}

void Mission::updateTrack()
{
    QVariantList mapPath;
    for (const auto &pt : qAsConst(m_items)) {
        if (pt.type == MissionItem::ItemType::TAKEOFF && m_home.isValid())
            mapPath.push_back(QVariant::fromValue(m_home));
        else if (pt.type == MissionItem::ItemType::RTL && m_home.isValid())
            mapPath.push_back(QVariant::fromValue(m_home));
        else if (pt.type == MissionItem::ItemType::SIMPLE_POINT)
            mapPath.push_back(QVariant::fromValue(QGeoCoordinate(pt.param_x, pt.param_y, pt.param_z)));
    }
    setMapPath(mapPath);
}

const QVariantList &Mission::mapPath() const
{
    return m_mapPath;
}

void Mission::setMapPath(const QVariantList &newMapPath)
{
    if (m_mapPath == newMapPath)
        return;
    m_mapPath = newMapPath;
    emit mapPathChanged();
}

void Mission::setHome(const QGeoCoordinate &newHome)
{
    m_home = newHome;
}
