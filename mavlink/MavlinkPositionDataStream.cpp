#include "MavlinkPositionDataStream.h"

MavlinkPositionDataStream::MavlinkPositionDataStream(QObject *parent)
    : PositionDataStream(parent)
{

}

bool MavlinkPositionDataStream::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
            mavlink_global_position_int_t pos;
            mavlink_msg_global_position_int_decode(&msg, &pos);
            QGeoCoordinate gps;
            gps.setLatitude((qreal)pos.lat / 1.e7);
            gps.setLongitude((qreal)pos.lon / 1.e7);
            gps.setAltitude((qreal)pos.alt / 1000.);
            emit onPositionChanged(gps);
            return true;
        }
        case MAVLINK_MSG_ID_ATTITUDE: {
            mavlink_attitude_t att;
            mavlink_msg_attitude_decode(&msg, &att);
            QVector3D vec{
                qRadiansToDegrees(att.roll),
                qRadiansToDegrees(att.pitch),
                qRadiansToDegrees(att.yaw)
            };
            emit onAttitudeChanged(vec);
            return true;
        }
        default:
            break;
    }
    return false;
}

void MavlinkPositionDataStream::onInit()
{

}
