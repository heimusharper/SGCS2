#ifndef MAVLINKMISSIONWRITEREQUEST_H
#define MAVLINKMISSIONWRITEREQUEST_H

#include "../streamer/MissionWriteRequest.h"
#include <QObject>
#include "MavlinkRequest.h"
#include <QDebug>

class MavlinkMissionWriteRequest : public MissionWriteRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkMissionWriteRequest(QObject *parent = nullptr);
    virtual ~MavlinkMissionWriteRequest();
    virtual bool ready() override;

    virtual void set(const QList<MissionItem *> &items) override;
    virtual void stop() override;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    enum State {
        UNDEFINED,
        SET_SIZE,
        SET_NEXT
    };
    State m_state = UNDEFINED;
    uint16_t m_nextPoint = 0;
    bool m_useInt = false;

    int getFrame(int f);
    int getFrameInt(int f);

    void resetTimers(int interval = 100);


    QList<mavlink_message_t> m_mission;
    QList<mavlink_message_t> m_mission_int;
};

#endif // MAVLINKMISSIONWRITEREQUEST_H
