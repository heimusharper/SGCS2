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
        m_baseMode = hb.base_mode;
        m_customMode = hb.custom_mode;

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
            m_isARMed = hb.base_mode & 0b10000000;
            checkMode();
            if (m_isFlight || m_isARMed)
            {

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
        //ack.command == MAV_CMD_COMPONENT_ARM_DISARM;
        //if (ack.result == )
        return true;
    }
    case MAVLINK_MSG_ID_VFR_HUD: {
        mavlink_vfr_hud_t hud;
        mavlink_msg_vfr_hud_decode(&msg, &hud);
        bool isFlight = false;
        switch (m_apMode) {
            case ModeHelper::APMode::ARDUPILOT_COPTER: {
                if (hud.throttle > 10)
                    isFlight = true;
                else
                    isFlight = false;
                break;
            }
            default:
                break;
        }
        if (m_isFlight != isFlight)
        {
            m_isFlight = isFlight;
            checkMode();
        }
        return true;
    }
    }
    return false;
}

void MavlinkMainDataStream::onInit()
{

}

void MavlinkMainDataStream::checkMode()
{
    int controlMode = ControlMode::UNSUPORTED;
    if (m_isARMed) {
        if (m_isFlight) {
            switch (m_apMode) {
            case ModeHelper::APMode::ARDUPILOT_COPTER: {
                    switch (m_customMode) {
                    case COPTER_MODE_ALT_HOLD:
                    case COPTER_MODE_GUIDED_NOGPS:
                    case COPTER_MODE_POSHOLD:
                        controlMode = ControlMode::GUIDED_RC;
                        break;
                    case COPTER_MODE_AUTO:
                        controlMode = ControlMode::AUTO;
                        break;
                    case COPTER_MODE_AUTO_RTL:
                    case COPTER_MODE_RTL:
                    case COPTER_MODE_SMART_RTL:
                        controlMode = ControlMode::RTL;
                        break;
                    case COPTER_MODE_FOLLOW:
                        controlMode = ControlMode::FOLOW;
                        break;
                    case COPTER_MODE_GUIDED:
                        controlMode = ControlMode::GUIDED;
                        break;
                    case COPTER_MODE_LAND:
                        controlMode = ControlMode::LAND;
                        break;
                    case COPTER_MODE_ZIGZAG:
                    case COPTER_MODE_THROW:
                    case COPTER_MODE_SYSTEMID:
                    case COPTER_MODE_STABILIZE:
                    case COPTER_MODE_ACRO:
                    case COPTER_MODE_AUTOROTATE:
                    case COPTER_MODE_AUTOTUNE:
                    case COPTER_MODE_AVOID_ADSB:
                    case COPTER_MODE_BRAKE:
                    case COPTER_MODE_CIRCLE:
                    case COPTER_MODE_DRIFT:
                    case COPTER_MODE_FLIP:
                    case COPTER_MODE_FLOWHOLD:
                    case COPTER_MODE_LOITER:
                    case COPTER_MODE_SPORT:
                    default:
                        break;
                    }
                    break;
                }
            case ModeHelper::APMode::ARDUPILOT_PLANE:
            case ModeHelper::APMode::ARDUPILOT_VTOL:
                break;
            case ModeHelper::APMode::PIXHAWK:
                break;
            default:
                break;
            }
        } else
            controlMode = ControlMode::ARMED;
    } else {
        controlMode = ControlMode::WAIT;
    }
    if (m_controlMode != controlMode)
    {
        m_controlMode = controlMode;
        emit onControlModeChanged(m_controlMode);
    }
}
