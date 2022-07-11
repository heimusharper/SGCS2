#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <QObject>
#include <QGeoCoordinate>

class MissionItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int delayOnWaypoint READ delayOnWaypoint WRITE setDelayOnWaypoint NOTIFY delayOnWaypointChanged)
    Q_PROPERTY(int jumpTo READ jumpTo WRITE setJumpTo NOTIFY jumpToChanged)
    Q_PROPERTY(int jumpRepeats READ jumpRepeats WRITE setJumpRepeats NOTIFY jumpRepeatsChanged)
    Q_PROPERTY(int distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int servo READ servo WRITE setServo NOTIFY servoChanged)
    Q_PROPERTY(int pwm READ pwm WRITE setPwm NOTIFY pwmChanged)
    Q_PROPERTY(int zoomPosition READ zoomPosition WRITE setZoomPosition NOTIFY zoomPositionChanged)
    Q_PROPERTY(bool autofocusNow READ autofocusNow WRITE setAutofocusNow NOTIFY autofocusNowChanged)
    Q_PROPERTY(bool shoot READ shoot WRITE setShoot NOTIFY shootChanged)
    Q_PROPERTY(int recordStart READ recordStart WRITE setRecordStart NOTIFY recordStartChanged)
    Q_PROPERTY(float gimbalPitch READ gimbalPitch WRITE setGimbalPitch NOTIFY gimbalPitchChanged)
    Q_PROPERTY(float gimbalRoll READ gimbalRoll WRITE setGimbalRoll NOTIFY gimbalRollChanged)
    Q_PROPERTY(float gimbalYaw READ gimbalYaw WRITE setGimbalYaw NOTIFY gimbalYawChanged)
    Q_PROPERTY(float shootOnTime READ shootOnTime WRITE setShootOnTime NOTIFY shootOnTimeChanged)
    Q_PROPERTY(float shootOnDistance READ shootOnDistance WRITE setShootOnDistance NOTIFY shootOnDistanceChanged)
    Q_PROPERTY(int frame READ frame WRITE setFrame NOTIFY frameChanged)


public:
    MissionItem(QObject *parent = nullptr);
    enum class ItemType : int
    {
        SIMPLE_POINT,
        TAKEOFF,
        RTL,
        LAND,
        JUMP,
        DELAY,
        DISTANCE,
        SPEED,
        SET_SERVO,
        ROI,
        CAMERA,
        GIMBAL,
        TRIGGER,
        PARACHUTE
    };
    Q_ENUMS(ItemType)
    enum class Frame : int
    {
        RELATIVE,
        RELIEF,
        ABSOLUTE,
        INVALID
    };
    Q_ENUMS(Frame)

    int type() const;
    void setType(int newType);

    const QGeoCoordinate &position() const;
    void setPosition(const QGeoCoordinate &newPosition);

    int delayOnWaypoint() const;
    void setDelayOnWaypoint(int newDelayOnWaypoint);

    int jumpTo() const;
    void setJumpTo(int newJumpTo);

    // -1 infinite
    int jumpRepeats() const;
    void setJumpRepeats(int newJumpRepeats);

    int distance() const;
    void setDistance(int newDistance);

    float speed() const;
    void setSpeed(float newSpeed);

    int servo() const;
    void setServo(int newServo);

    int pwm() const;
    void setPwm(int newPwm);

    int zoomPosition() const;
    void setZoomPosition(int newZoomPosition);

    bool autofocusNow() const;
    void setAutofocusNow(bool newAutofocusNow);

    bool shoot() const;
    void setShoot(bool newShoot);

    int recordStart() const;
    void setRecordStart(int newRecordStart);

    float gimbalPitch() const;
    void setGimbalPitch(float newGimbalPitch);

    float gimbalRoll() const;
    void setGimbalRoll(float newGimbalRoll);

    float gimbalYaw() const;
    void setGimbalYaw(float newGimbalYaw);

    float shootOnTime() const;
    void setShootOnTime(float newShootOnTime);

    float shootOnDistance() const;
    void setShootOnDistance(float newShootOnDistance);

    int frame() const;
    void setFrame(int newFrame);

signals:
    void typeChanged();

    void positionChanged();

    void delayOnWaypointChanged();

    void jumpToChanged();

    void jumpRepeatsChanged();

    void distanceChanged();

    void speedChanged();

    void servoChanged();

    void pwmChanged();

    void zoomPositionChanged();

    void autofocusNowChanged();

    void shootChanged();

    void recordStartChanged();

    void gimbalPitchChanged();

    void gimbalRollChanged();

    void gimbalYawChanged();

    void shootOnTimeChanged();

    void shootOnDistanceChanged();

    void frameChanged();

private:
    int m_type;
    QGeoCoordinate m_position;

    int m_delayOnWaypoint = -1;
    int m_jumpTo = 0;
    int m_jumpRepeats = -1;
    int m_distance = 0;
    float m_speed = -1;
    int m_servo = -1;
    int m_pwm = -1;
    int m_zoomPosition = -1;
    bool m_autofocusNow = -1;
    bool m_shoot = -1;
    int m_recordStart = 0;
    float m_gimbalPitch = 0;
    float m_gimbalRoll = 0;
    float m_gimbalYaw = 0;
    float m_shootOnTime = 0;
    float m_shootOnDistance = 0;
    int m_frame = (int)Frame::ABSOLUTE;
};

#endif // MISSIONITEM_H
