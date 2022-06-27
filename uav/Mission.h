#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QGeoCoordinate>

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

    explicit Mission(QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override
    {
        return m_items.size();
    }

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[TypeRole] = "type";
        roles[Latitude] = "lat";
        roles[Longitude] = "lon";
        roles[Altitude] = "alt";

        return roles;
    }
    QVariant data(const QModelIndex& index, int role) const override
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
    Q_INVOKABLE MissionItem *itemAt(int index)
    {
        return m_items.at(index);
    }

    Q_INVOKABLE void insertSimplePoint(const QGeoCoordinate &pos)
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        MissionItem *item = new MissionItem;
        item->setPosition(pos);
        m_items.push_back(item);
        endInsertRows();
    }
    Q_INVOKABLE void removeOne(int index)
    {
        if (index < m_items.size()) {
            beginRemoveRows(QModelIndex(), index, index);
            m_items.takeAt(index)->deleteLater();
            endRemoveRows();
        }
    }

private:

    QList<MissionItem*> m_items;

signals:

};

#endif // MISSION_H
