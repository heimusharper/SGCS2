#ifndef MAVLINKPINGREQUEST_H
#define MAVLINKPINGREQUEST_H
#include "MavlinkRequest.h"
#include <QDebug>
#include <QObject>
#include <QTime>

class MavlinkPingRequest : public MavlinkRequest
{
public:
    explicit MavlinkPingRequest();
    virtual ~MavlinkPingRequest() = default;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    bool index = false;
    uint32_t m_pingSeq = 0;
};

#endif // MAVLINKPINGREQUEST_H
