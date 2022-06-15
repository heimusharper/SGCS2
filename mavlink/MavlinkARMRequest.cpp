#include "MavlinkARMRequest.h"

MavlinkARMRequest::MavlinkARMRequest(Mode mode, QObject *parent)
    : ARMRequest{mode, parent}
    , MavlinkRequest{}
{
    setMode(mode);
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
        uint8_t base = ModeHelper::getBaseMode(APMODE);
        uint32_t custom = ModeHelper::getModeARMable(APMODE);
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
    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&msg, &hb);
        m_baseMode = hb.base_mode;
        m_customMode = hb.custom_mode;
        break;
    }
    case MAVLINK_MSG_ID_COMMAND_ACK: {
        mavlink_command_ack_t ack;
        mavlink_msg_command_ack_decode(&msg, &ack);
        if (m_state == State::WAIT_FOR_CURRENT_MODE &&
            ack.command == MAVLINK_MSG_ID_SET_MODE) {
            // wait for set mode
            if (ack.result == MAV_RESULT_ACCEPTED) {
                setMode(ARMRequest::ARM, true);
            } else {

            }
        }


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
