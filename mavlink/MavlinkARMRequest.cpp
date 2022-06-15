#include "MavlinkARMRequest.h"

MavlinkARMRequest::MavlinkARMRequest(Mode mode, QObject *parent)
    : ARMRequest{mode, parent}
    , MavlinkRequest{}
{
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = 100;

    m_state = State::UNDEFINED;
    switch (m_mode) {
    case Mode::ARM:
        m_state = State::WAIT_FOR_CURRENT_MODE;
        qDebug() << "try to ARM";
        break;
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

bool MavlinkARMRequest::ready()
{
    if (m_state == State::UNDEFINED)
        return false;
    return MavlinkRequest::ready();
}

mavlink_message_t MavlinkARMRequest::construct()
{
    mavlink_message_t m_request;
    switch (m_state) {
    case State::WAIT_FOR_CURRENT_MODE:
    {
        uint8_t base = 0;
        uint32_t custom = ModeHelper::getModeARMable(APMODE);
        switch (APMODE) {
            case ModeHelper::APMode::ARDUPILOT_COPTER:
            case ModeHelper::APMode::ARDUPILOT_PLANE:
            case ModeHelper::APMode::ARDUPILOT_VTOL: {

                base = base | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED |
                       MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_AUTO_ENABLED | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
                break;
            }
            case ModeHelper::APMode::PIXHAWK:
            default: {

                base = base | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED |
                       MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_AUTO_ENABLED | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
                break;
            }
        }

            qDebug() << "do set mode..." << base << custom;
        mavlink_msg_set_mode_pack(GCSID, COMPID, &m_request, APID, base, custom);
        break;
    }
    case State::ARM:
        mavlink_msg_command_long_pack(GCSID, COMPID, &m_request,
                                      APID, APCOMP, MAV_CMD_COMPONENT_ARM_DISARM,
                                      0, 1, 0, 0, 0, 0, 0, 0);
        qDebug() << "do ARM...";
        break;
    case State::DISARM:
        mavlink_msg_command_long_pack(GCSID, COMPID, &m_request,
                                      APID, APCOMP, MAV_CMD_COMPONENT_ARM_DISARM,
                                      0, 0, 0, 0, 0, 0, 0, 0);
        qDebug() << "do DisARM...";
        break;
    case State::TAKEOFF:
        mavlink_msg_command_long_pack(GCSID, COMPID, &m_request,
                                      APID, APCOMP, MAV_CMD_NAV_TAKEOFF,
                                      0, 0, 0, 0, 0, 0, 0, 20);
        qDebug() << "do Takeoff...";
        break;
    case State::MISSION_START:
        mavlink_msg_command_long_pack(GCSID, COMPID, &m_request,
                                      APID, APCOMP, MAV_CMD_MISSION_START,
                                      0, 0, 0, 0, 0, 0, 0, 0);
        qDebug() << "do mission start...";
        break;
    case State::UNDEFINED:
        break;
    default:
        break;
    }
    return m_request;
}

bool MavlinkARMRequest::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid) {
    case MAVLINK_MSG_ID_COMMAND_ACK: {
        mavlink_command_ack_t ack;
        mavlink_msg_command_ack_decode(&msg, &ack);
        qDebug() << "ACK" << ack.command << ack.result;
        if (ack.result == MAV_RESULT_ACCEPTED) {
            switch (ack.command) {
            case MAV_CMD_COMPONENT_ARM_DISARM: {
                switch (m_state) {
                case State::ARM:
                    m_empty = true;
                    emit onARMED();
                    break;
                case State::DISARM:
                    emit onDISARMED();
                    m_empty = true;
                    break;
                default:
                    break;
                }
                break;
            }
            case MAV_CMD_NAV_TAKEOFF: {
                if (m_state == State::TAKEOFF)
                {
                    emit onTAKEOFF();
                    m_empty = true;
                }
                break;
            }
            case MAV_CMD_MISSION_START: {
                if (m_state == State::MISSION_START)
                {
                    emit onMISSIONSTART();
                    m_empty = true;
                }
                break;
            }
            default:
                break;
            }
        }
        break;
    }
    default:
        break;
    }
    return false;
}

void MavlinkARMRequest::onInit()
{

}
