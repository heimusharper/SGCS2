#ifndef MAVLINKARMREQUEST_H
#define MAVLINKARMREQUEST_H
#include "../streamer/ARMRequest.h"
#include "MavlinkRequest.h"
/*!
 * \brief The MavlinkARMRequest class
 *
 * ARM processor
 *
 * 1. select armable mode
 * 2. arm
 *
 * or
 *
 * 1. takeoff
 *
 */
class MavlinkARMRequest : public ARMRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkARMRequest(ARMRequest::Mode mode, QObject *parent = nullptr);
    virtual ~MavlinkARMRequest() = default;
    virtual bool ready() override;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    enum State {
        WAIT_FOR_CURRENT_MODE,
        ARM,
        DISARM,
        TAKEOFF,
        MISSION_START,
        UNDEFINED
    };

    State m_state = State::WAIT_FOR_CURRENT_MODE;

signals:

    void onARMED();
    void onDISARMED();
    void onTAKEOFF();
    void onMISSIONSTART();
};

#endif // MAVLINKARMREQUEST_H
