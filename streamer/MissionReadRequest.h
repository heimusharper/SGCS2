#ifndef MISSIONREADREQUEST_H
#define MISSIONREADREQUEST_H

#include <QObject>
#include "../uav/MissionItem.h"

class MissionReadRequest : public QObject
{
    Q_OBJECT
public:
    explicit MissionReadRequest(QObject *parent = nullptr)
        : QObject(parent)
    {
    }
    virtual void stop() = 0;

signals:

    void onItem(uint16_t seq, const MissionItem &it);
    void progress(float stat, bool err);
    void onError(const QString &err);
};

#endif // MISSIONREADREQUEST_H
