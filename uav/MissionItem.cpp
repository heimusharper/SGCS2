#include "MissionItem.h"

MissionItem::MissionItem(QObject *parent)
    : QObject{parent}
{

}

int MissionItem::type() const
{
    return m_type;
}

void MissionItem::setType(int newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

const QGeoCoordinate &MissionItem::position() const
{
    return m_position;
}

void MissionItem::setPosition(const QGeoCoordinate &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}

int MissionItem::delayOnWaypoint() const
{
    return m_delayOnWaypoint;
}

void MissionItem::setDelayOnWaypoint(int newDelayOnWaypoint)
{
    if (m_delayOnWaypoint == newDelayOnWaypoint)
        return;
    m_delayOnWaypoint = newDelayOnWaypoint;
    emit delayOnWaypointChanged();
}

int MissionItem::jumpTo() const
{
    return m_jumpTo;
}

void MissionItem::setJumpTo(int newJumpTo)
{
    if (m_jumpTo == newJumpTo)
        return;
    m_jumpTo = newJumpTo;
    emit jumpToChanged();
}

int MissionItem::jumpRepeats() const
{
    return m_jumpRepeats;
}

void MissionItem::setJumpRepeats(int newJumpRepeats)
{
    if (m_jumpRepeats == newJumpRepeats)
        return;
    m_jumpRepeats = newJumpRepeats;
    emit jumpRepeatsChanged();
}

int MissionItem::distance() const
{
    return m_distance;
}

void MissionItem::setDistance(int newDistance)
{
    if (m_distance == newDistance)
        return;
    m_distance = newDistance;
    emit distanceChanged();
}

float MissionItem::speed() const
{
    return m_speed;
}

void MissionItem::setSpeed(float newSpeed)
{
    if (qFuzzyCompare(m_speed, newSpeed))
        return;
    m_speed = newSpeed;
    emit speedChanged();
}

int MissionItem::servo() const
{
    return m_servo;
}

void MissionItem::setServo(int newServo)
{
    if (m_servo == newServo)
        return;
    m_servo = newServo;
    emit servoChanged();
}

int MissionItem::pwm() const
{
    return m_pwm;
}

void MissionItem::setPwm(int newPwm)
{
    if (m_pwm == newPwm)
        return;
    m_pwm = newPwm;
    emit pwmChanged();
}

int MissionItem::zoomPosition() const
{
    return m_zoomPosition;
}

void MissionItem::setZoomPosition(int newZoomPosition)
{
    if (m_zoomPosition == newZoomPosition)
        return;
    m_zoomPosition = newZoomPosition;
    emit zoomPositionChanged();
}

bool MissionItem::autofocusNow() const
{
    return m_autofocusNow;
}

void MissionItem::setAutofocusNow(bool newAutofocusNow)
{
    if (m_autofocusNow == newAutofocusNow)
        return;
    m_autofocusNow = newAutofocusNow;
    emit autofocusNowChanged();
}

bool MissionItem::shoot() const
{
    return m_shoot;
}

void MissionItem::setShoot(bool newShoot)
{
    if (m_shoot == newShoot)
        return;
    m_shoot = newShoot;
    emit shootChanged();
}

int MissionItem::recordStart() const
{
    return m_recordStart;
}

void MissionItem::setRecordStart(int newRecordStart)
{
    if (m_recordStart == newRecordStart)
        return;
    m_recordStart = newRecordStart;
    emit recordStartChanged();
}

float MissionItem::gimbalPitch() const
{
    return m_gimbalPitch;
}

void MissionItem::setGimbalPitch(float newGimbalPitch)
{
    if (qFuzzyCompare(m_gimbalPitch, newGimbalPitch))
        return;
    m_gimbalPitch = newGimbalPitch;
    emit gimbalPitchChanged();
}

float MissionItem::gimbalRoll() const
{
    return m_gimbalRoll;
}

void MissionItem::setGimbalRoll(float newGimbalRoll)
{
    if (qFuzzyCompare(m_gimbalRoll, newGimbalRoll))
        return;
    m_gimbalRoll = newGimbalRoll;
    emit gimbalRollChanged();
}

float MissionItem::gimbalYaw() const
{
    return m_gimbalYaw;
}

void MissionItem::setGimbalYaw(float newGimbalYaw)
{
    if (qFuzzyCompare(m_gimbalYaw, newGimbalYaw))
        return;
    m_gimbalYaw = newGimbalYaw;
    emit gimbalYawChanged();
}

float MissionItem::shootOnTime() const
{
    return m_shootOnTime;
}

void MissionItem::setShootOnTime(float newShootOnTime)
{
    if (qFuzzyCompare(m_shootOnTime, newShootOnTime))
        return;
    m_shootOnTime = newShootOnTime;
    emit shootOnTimeChanged();
}

float MissionItem::shootOnDistance() const
{
    return m_shootOnDistance;
}

void MissionItem::setShootOnDistance(float newShootOnDistance)
{
    if (qFuzzyCompare(m_shootOnDistance, newShootOnDistance))
        return;
    m_shootOnDistance = newShootOnDistance;
    emit shootOnDistanceChanged();
}

int MissionItem::frame() const
{
    return m_frame;
}

void MissionItem::setFrame(int newFrame)
{
    if (m_frame == newFrame)
        return;
    m_frame = newFrame;
    emit frameChanged();
}
