#ifndef MAVLINKARMREQUEST_H
#define MAVLINKARMREQUEST_H
#include "../streamer/ARMRequest.h"
#include "MavlinkRequest.h"
#include <QDebug>
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

    void setMode(ARMRequest::Mode mode, bool force = false) {
        m_mode = mode;
        m_maxMessageLiveTimeMs = 2000;
        m_messageIntervalMs = 100;
        m_state = State::UNDEFINED;
        switch (m_mode) {
        case Mode::ARM: {
            if (force)
                m_state = State::ARM;
            else
                m_state = State::WAIT_FOR_CURRENT_MODE;
            qDebug() << "try to ARM";
            break;
        }
        case Mode::DISARM:
            m_state = State::DISARM;
            qDebug() << "try to DisARM";
            break;
        case Mode::TAKEOFF:
            m_state = State::TAKEOFF;
            qDebug() << "try to Takeoff";
            break;
        case Mode::MISSION_START:
            m_state = State::MISSION_START;
            qDebug() << "try to Mission start";
            break;
        default:
            break;
        }
    }

    enum State {
        WAIT_FOR_CURRENT_MODE,
        ARM,
        DISARM,
        TAKEOFF,
        MISSION_START,
        UNDEFINED
    };

    State m_state = State::WAIT_FOR_CURRENT_MODE;

    uint8_t  m_baseMode;
    uint32_t m_customMode;

signals:

    void onARMED();
    void onDISARMED();
    void onTAKEOFF();
    void onMISSIONSTART();
};

#endif // MAVLINKARMREQUEST_H
