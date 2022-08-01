#include "MavlinkErrorStream.h"

MavlinkErrorStream::MavlinkErrorStream(QObject *parent)
    : ErrorStreamer{parent}
{

}

bool MavlinkErrorStream::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid){
    case MAVLINK_MSG_ID_SYS_STATUS:
    {
        States newState;
        mavlink_sys_status_t status;
        mavlink_msg_sys_status_decode(&msg, &status);

        auto check = [status](States::State &target, const int key) {
            if (status.onboard_control_sensors_present & key != 0 &&
                status.onboard_control_sensors_enabled & key != 0) {
                if (status.onboard_control_sensors_health & key == 0)
                    target = States::State::ERROR;
                else
                    target = States::State::READY;
            } else
                target = States::State::NOT_PRESENT;
        };
        check(newState.gyro, MAV_SYS_STATUS_SENSOR_3D_GYRO | MAV_SYS_STATUS_SENSOR_3D_GYRO2);
        check(newState.accel, MAV_SYS_STATUS_SENSOR_3D_ACCEL | MAV_SYS_STATUS_SENSOR_3D_ACCEL2);
        check(newState.mag, MAV_SYS_STATUS_SENSOR_3D_MAG | MAV_SYS_STATUS_SENSOR_3D_MAG2);
        check(newState.absPressure, MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
        check(newState.diffPressure, MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
        check(newState.gps, MAV_SYS_STATUS_SENSOR_GPS);
        check(newState.opticalFlow, MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW);
        check(newState.visionPosition, MAV_SYS_STATUS_SENSOR_VISION_POSITION);
        check(newState.laserPosition, MAV_SYS_STATUS_SENSOR_LASER_POSITION);
        check(newState.angularRateControl, MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL);
        check(newState.attitudeStablization, MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION);
        check(newState.yawControl, MAV_SYS_STATUS_SENSOR_YAW_POSITION);
        check(newState.zControl, MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL);
        check(newState.xyControl, MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL);
        check(newState.motorOut, MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS);
        check(newState.rc, MAV_SYS_STATUS_SENSOR_RC_RECEIVER);
        check(newState.geoFence, MAV_SYS_STATUS_GEOFENCE);
        check(newState.ahrs, MAV_SYS_STATUS_AHRS);
        check(newState.terrain, MAV_SYS_STATUS_TERRAIN);
        check(newState.reverseMotor, MAV_SYS_STATUS_REVERSE_MOTOR);
        check(newState.log, MAV_SYS_STATUS_LOGGING);
        check(newState.battery, MAV_SYS_STATUS_SENSOR_BATTERY);
        check(newState.proximity, MAV_SYS_STATUS_SENSOR_PROXIMITY);
        check(newState.satcom, MAV_SYS_STATUS_SENSOR_SATCOM);
        check(newState.obstacleAviodance, MAV_SYS_STATUS_OBSTACLE_AVOIDANCE);
        check(newState.propulsion, MAV_SYS_STATUS_SENSOR_PROPULSION);



        if (newState != m_state) {
            m_state = newState;
            emit onStatesChenged(m_state);
        }

        break;
    }
    }
    return false;
}

void MavlinkErrorStream::onInit()
{
}
