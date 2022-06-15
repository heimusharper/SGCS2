#include "MavlinkMainDataStream.h"

MavlinkMainDataStream::MavlinkMainDataStream(QObject *parent)
    : MainDataStream{parent}
{

}

int MavlinkMainDataStream::convertUAVType(int t) const
{
    switch (t) {
    case MAV_TYPE_VTOL_FIXEDROTOR:
    case MAV_TYPE_VTOL_RESERVED4:
    case MAV_TYPE_VTOL_RESERVED5:
    case MAV_TYPE_VTOL_TAILSITTER:
    case MAV_TYPE_VTOL_TAILSITTER_DUOROTOR:
    case MAV_TYPE_VTOL_TAILSITTER_QUADROTOR:
    case MAV_TYPE_VTOL_TILTROTOR:
        return UavType::VTOL;
    case MAV_TYPE_HELICOPTER:
    case MAV_TYPE_HEXAROTOR:
    case MAV_TYPE_TRICOPTER:
    case MAV_TYPE_OCTOROTOR:
    case MAV_TYPE_QUADROTOR:
        return UavType::COPTER;
    case MAV_TYPE_FIXED_WING:
        return UavType::PLANE;
    default:
        return UavType::UNDEFINED;
        break;
    }
    return UavType::UNDEFINED;
}

bool MavlinkMainDataStream::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&msg, &hb);

        if (!m_apInitiated) {
            // initiate autopilot
            int uavType = convertUAVType(hb.type);

            ModeHelper::APMode apMode = ModeHelper::APMode::PIXHAWK;
            switch (hb.autopilot) {
            case MAV_AUTOPILOT_ARDUPILOTMEGA: {
                switch (uavType) {
                case UavType::COPTER:
                    apMode = ModeHelper::APMode::ARDUPILOT_COPTER;
                    break;
                case UavType::PLANE:
                    apMode = ModeHelper::APMode::ARDUPILOT_PLANE;
                    break;
                case UavType::VTOL:
                    apMode = ModeHelper::APMode::ARDUPILOT_VTOL;
                    break;
                default:
                    break;
                }
                break;
            }
            default:
                apMode = ModeHelper::APMode::PIXHAWK;
                break;
            }

            if (uavType == UavType::COPTER || uavType == UavType::PLANE ||
                uavType == UavType::VTOL)
            {
                m_apInitiated = true;
                emit onFoundAutopilot(msg.sysid, msg.compid, apMode);
            }
        }
        if (m_apInitiated) {
            int uavType = convertUAVType(hb.type);
            if (uavType != m_lastUavType) {
                m_lastUavType = uavType;
                if (m_lastUavType == UavType::UNDEFINED)
                    return false;
                else
                    emit onUavTypeChanged(uavType);
            }
            const bool armed = hb.base_mode & 0b10000000;
            if (m_isFlight || armed)
            {
                if (m_armProcess == ARM_PROCESS::ARM)
                {

                }

            } else {
                // wait for commands
            }
        }
        return true;
    }
    case MAVLINK_MSG_ID_COMMAND_ACK:
    {
        mavlink_command_ack_t ack;
        mavlink_msg_command_ack_decode(&msg, &ack);
        ack.command == MAV_CMD_COMPONENT_ARM_DISARM;
        //if (ack.result == )
        return true;
    }
    case MAVLINK_MSG_ID_VFR_HUD: {
        return true;
    }
    }
    return false;
}

void MavlinkMainDataStream::onInit()
{

}
