#include "MissionItem.h"

MissionItem::MissionItem(QObject *parent)
    : QObject{parent}
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
float MissionItem::property1() const
{
    return m_property1;
}

void MissionItem::setProperty1(float newProperty1)
{
    if (qFuzzyCompare(m_property1, newProperty1))
        return;
    m_property1 = newProperty1;
    emit property1Changed();
}

float MissionItem::property2() const
{
    return m_property2;
}

void MissionItem::setProperty2(float newProperty2)
{
    if (qFuzzyCompare(m_property2, newProperty2))
        return;
    m_property2 = newProperty2;
    emit property2Changed();
}

float MissionItem::property3() const
{
    return m_property3;
}

void MissionItem::setProperty3(float newProperty3)
{
    if (qFuzzyCompare(m_property3, newProperty3))
        return;
    m_property3 = newProperty3;
    emit property3Changed();
}

float MissionItem::property4() const
{
    return m_property4;
}

void MissionItem::setProperty4(float newProperty4)
{
    if (qFuzzyCompare(m_property4, newProperty4))
        return;
    m_property4 = newProperty4;
    emit property4Changed();
}

float MissionItem::property5() const
{
    return m_property5;
}

void MissionItem::setProperty5(float newProperty5)
{
    if (qFuzzyCompare(m_property5, newProperty5))
        return;
    m_property5 = newProperty5;
    emit property5Changed();
}

float MissionItem::property6() const
{
    return m_property6;
}

void MissionItem::setProperty6(float newProperty6)
{
    if (qFuzzyCompare(m_property6, newProperty6))
        return;
    m_property6 = newProperty6;
    emit property6Changed();
}

float MissionItem::property7() const
{
    return m_property7;
}

void MissionItem::setProperty7(float newProperty7)
{
    if (qFuzzyCompare(m_property7, newProperty7))
        return;
    m_property7 = newProperty7;
    emit property7Changed();
}
