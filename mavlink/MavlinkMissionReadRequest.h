#ifndef MAVLINKMISSIONREADREQUEST_H
#define MAVLINKMISSIONREADREQUEST_H
#include "../streamer/MissionReadRequest.h"
#include <QObject>
#include <QDebug>
#include "MavlinkRequest.h"

class MavlinkMissionReadRequest : public MissionReadRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkMissionReadRequest(QObject *parent = nullptr);
    virtual ~MavlinkMissionReadRequest();
    virtual bool ready() override;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    enum State {
        UNDEFINED,
        GET_SIZE,
        GET_NEXT,
        SET_ACK
    };
    State m_state = UNDEFINED;
    uint16_t m_nextPoint = 0;
    uint16_t m_missinFull = 0;

    void resetTimers(int interval = 100);
signals:

};

#endif // MAVLINKMISSIONREADREQUEST_H
