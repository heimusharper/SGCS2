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
    enum Errors {
        ERR_FAILED_GET_COUNT,
        ERR_FAILED_GET_INDEX
    };

    virtual void stop() = 0;

signals:

    // void onError(MissionReadRequest::Errors err);
    void onItem(uint16_t seq, MissionItem *it);
    void progress(float stat);
};

#endif // MISSIONREADREQUEST_H
