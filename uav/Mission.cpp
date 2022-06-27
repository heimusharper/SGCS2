#include "Mission.h"

Mission::Mission(QObject *parent)
    : QAbstractListModel{parent}
{

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
