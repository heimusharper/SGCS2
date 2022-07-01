#include "MavlinkPhotoPayloadStream.h"

MavlinkPhotoPayloadStream::MavlinkPhotoPayloadStream(QObject *parent)
    : PhotoPayloadStream{parent}, MavlinkRequest()
{
    m_messageIntervalMs = 40;
}

MavlinkPhotoPayloadStream::~MavlinkPhotoPayloadStream()
{

}

bool MavlinkPhotoPayloadStream::ready()
{
    return m_waitForTakeOneShot;
}

bool MavlinkPhotoPayloadStream::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_CAMERA_FEEDBACK: {
        mavlink_camera_feedback_t feedback;
        mavlink_msg_camera_feedback_decode(&msg, &feedback);
        emit onTakeShot(feedback.completed_captures,
                        QGeoCoordinate((double)feedback.lat / 1.e7,
                                       (double)feedback.lng / 1.e7,
                                       (double)feedback.alt_msl));
        return true;
    }
    }
    return false;
}

void MavlinkPhotoPayloadStream::onInit()
{

}

void MavlinkPhotoPayloadStream::takeOneShot()
{
    m_waitForTakeOneShot = true;
}

mavlink_message_t MavlinkPhotoPayloadStream::construct()
{
    mavlink_message_t message;
    mavlink_msg_digicam_control_pack(GCSID, COMPID, &message, APID, APCOMP,
                                     0, 0, 0, 0, 1, 0, 0, 0);
    m_waitForTakeOneShot = false;
    qDebug() << "take one shot";
    return message;
}
