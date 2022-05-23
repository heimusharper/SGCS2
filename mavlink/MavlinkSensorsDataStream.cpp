#include "MavlinkSensorsDataStream.h"

MavlinkSensorsDataStream::MavlinkSensorsDataStream(QObject *parent)
    : SensorsDataStream{parent}
{

}

bool MavlinkSensorsDataStream::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_GPS_RAW_INT: {
        mavlink_gps_raw_int_t gps;
        mavlink_msg_gps_raw_int_decode(&msg, &gps);
        if (fixType != gps.fix_type) {
            fixType = gps.fix_type;
            switch (gps.fix_type) {
            case GPS_FIX_TYPE_NO_GPS:
            case GPS_FIX_TYPE_NO_FIX:
                emit onGPSStateChanged((int)GpsStatus::NA);
                break;
            case GPS_FIX_TYPE_2D_FIX:
                emit onGPSStateChanged((int)GpsStatus::FIX2D);
                break;
            case GPS_FIX_TYPE_3D_FIX:
                emit onGPSStateChanged((int)GpsStatus::FIX3D);
                break;
            case GPS_FIX_TYPE_DGPS:
                emit onGPSStateChanged((int)GpsStatus::DGPS);
                break;
            case GPS_FIX_TYPE_RTK_FLOAT:
                emit onGPSStateChanged((int)GpsStatus::RTKFLOAT);
                break;
            case GPS_FIX_TYPE_RTK_FIXED:
                emit onGPSStateChanged((int)GpsStatus::RTKFIX);
                break;
            case GPS_FIX_TYPE_STATIC:
                emit onGPSStateChanged((int)GpsStatus::STATIC);
                break;
            case GPS_FIX_TYPE_PPP:
                emit onGPSStateChanged((int)GpsStatus::PPP);
                break;
            default:
                break;
            }
        }
        return true;
    }
    }
    return false;
}

void MavlinkSensorsDataStream::onInit()
{

}
