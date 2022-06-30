#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <QObject>
#include <QGeoCoordinate>

class MissionItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(float property1 READ property1 WRITE setProperty1 NOTIFY property1Changed)
    Q_PROPERTY(float property2 READ property2 WRITE setProperty2 NOTIFY property2Changed)
    Q_PROPERTY(float property3 READ property3 WRITE setProperty3 NOTIFY property3Changed)
    Q_PROPERTY(float property4 READ property4 WRITE setProperty4 NOTIFY property4Changed)
    Q_PROPERTY(float property5 READ property5 WRITE setProperty5 NOTIFY property5Changed)
    Q_PROPERTY(float property6 READ property6 WRITE setProperty6 NOTIFY property6Changed)
    Q_PROPERTY(float property7 READ property7 WRITE setProperty7 NOTIFY property7Changed)

public:
    MissionItem(QObject *parent);
    enum ItemType
    {
        SIMPLE_POINT
    };
    Q_ENUMS(ItemType)

    int type() const;
    void setType(int newType);

    const QGeoCoordinate &position() const;
    void setPosition(const QGeoCoordinate &newPosition);

    float property1() const;
    void setProperty1(float newProperty1);

    float property2() const;
    void setProperty2(float newProperty2);

    float property3() const;
    void setProperty3(float newProperty3);

    float property4() const;
    void setProperty4(float newProperty4);

    float property5() const;
    void setProperty5(float newProperty5);

    float property6() const;
    void setProperty6(float newProperty6);

    float property7() const;
    void setProperty7(float newProperty7);

signals:
    void typeChanged();

    void positionChanged();

    void property1Changed();

    void property2Changed();

    void property3Changed();

    void property4Changed();

    void property5Changed();

    void property6Changed();

    void property7Changed();

private:
    int m_type;
    QGeoCoordinate m_position;

    float m_property1;
    float m_property2;
    float m_property3;
    float m_property4;
    float m_property5;
    float m_property6;
    float m_property7;
};

#endif // MISSIONITEM_H
