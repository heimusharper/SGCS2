#ifndef ERRORSTREAMER_H
#define ERRORSTREAMER_H

#include <QObject>

class ErrorStreamer : public QObject
{
    Q_OBJECT
public:
    struct States {
        enum State {
            NOT_PRESENT,
            ERROR,
            READY
        };

        State gyro = NOT_PRESENT;
        State accel = NOT_PRESENT;
        State mag = NOT_PRESENT;
        State absPressure = NOT_PRESENT;
        State diffPressure = NOT_PRESENT;
        State gps = NOT_PRESENT;
        State opticalFlow = NOT_PRESENT;
        State visionPosition = NOT_PRESENT;
        State laserPosition = NOT_PRESENT;
        State angularRateControl = NOT_PRESENT;
        State attitudeStablization = NOT_PRESENT;
        State yawControl = NOT_PRESENT;
        State zControl = NOT_PRESENT;
        State xyControl = NOT_PRESENT;
        State motorOut = NOT_PRESENT;
        State rc = NOT_PRESENT;
        State geoFence = NOT_PRESENT;
        State ahrs = NOT_PRESENT;
        State terrain = NOT_PRESENT;
        State reverseMotor = NOT_PRESENT;
        State log = NOT_PRESENT;
        State battery = NOT_PRESENT;
        State proximity = NOT_PRESENT;
        State satcom = NOT_PRESENT;
        State obstacleAviodance = NOT_PRESENT;
        State propulsion = NOT_PRESENT;

        bool operator !=(const States& s) const{
            return s.gyro != gyro ||
                s.accel != accel ||
                s.mag != mag ||
                s.absPressure != absPressure ||
                s.diffPressure != diffPressure ||
                s.gps != gps ||
                s.opticalFlow != opticalFlow ||
                s.visionPosition != visionPosition ||
                s.laserPosition != laserPosition ||
                s.angularRateControl != angularRateControl ||
                s.attitudeStablization != attitudeStablization ||
                s.yawControl != yawControl ||
                s.zControl != zControl ||
                s.xyControl != xyControl ||
                s.motorOut != motorOut ||
                s.rc != rc ||
                s.geoFence != geoFence ||
                s.ahrs != ahrs ||
                s.terrain != terrain ||
                s.reverseMotor != reverseMotor ||
                s.log != log ||
                s.battery != battery ||
                s.proximity != proximity ||
                s.satcom != satcom ||
                s.obstacleAviodance != obstacleAviodance ||
                s.propulsion != propulsion;
        }
    };

    explicit ErrorStreamer(QObject *parent = nullptr)
        : QObject(parent){

    }
    virtual ~ErrorStreamer() = default;

signals:
    void onStatesChenged(const States &s);
};

#endif // ERRORSTREAMER_H
