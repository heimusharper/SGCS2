#ifndef MISSIONWRITEREQUEST_H
#define MISSIONWRITEREQUEST_H

#include <QObject>
#include "../uav/MissionItem.h"

class MissionWriteRequest : public QObject
{
    Q_OBJECT
public:
    explicit MissionWriteRequest(QObject *parent = nullptr)
        : QObject(parent)
    {
    }
    virtual ~MissionWriteRequest()
    {

    }

    virtual void set(const QList<MissionItem*> &it) = 0;
    virtual void stop() = 0;

signals:
    void progress(float stat);
};

#endif // MISSIONWRITEREQUEST_H
