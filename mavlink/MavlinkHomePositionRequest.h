#ifndef MAVLINKHOMEPOSITIONREQUEST_H
#define MAVLINKHOMEPOSITIONREQUEST_H
#include "../streamer/HomePositionRequest.h"
#include "MavlinkRequest.h"

class MavlinkHomePositionRequest : public HomePositionRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    MavlinkHomePositionRequest(QObject *parent);
    virtual ~MavlinkHomePositionRequest() = default;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;
private:
    mavlink_message_t m_request;
};

#endif // MAVLINKHOMEPOSITIONSTREAMER_H
