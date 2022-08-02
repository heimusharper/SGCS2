#ifndef FAILSAFE_H
#define FAILSAFE_H

#include <QObject>
#include "../streamer/DataStreamer.h"
#include <QDebug>

class Failsafe : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int stateGyros READ stateGyros WRITE setStateGyros NOTIFY stateGyrosChanged)
    Q_PROPERTY(int stateAccels READ stateAccels WRITE setStateAccels NOTIFY stateAccelsChanged)
    Q_PROPERTY(int stateMagnetometer READ stateMagnetometer WRITE setStateMagnetometer NOTIFY stateMagnetometerChanged)
    Q_PROPERTY(int stateAbsPressure READ stateAbsPressure WRITE setStateAbsPressure NOTIFY stateAbsPressureChanged)
    Q_PROPERTY(int stateDiffPressure READ stateDiffPressure WRITE setStateDiffPressure NOTIFY stateDiffPressureChanged)
    Q_PROPERTY(int stateGPS READ stateGPS WRITE setStateGPS NOTIFY stateGPSChanged)
    Q_PROPERTY(int stateOpticalFlow READ stateOpticalFlow WRITE setStateOpticalFlow NOTIFY stateOpticalFlowChanged)
    Q_PROPERTY(int stateVisionPosition READ stateVisionPosition WRITE setStateVisionPosition NOTIFY stateVisionPositionChanged)
    Q_PROPERTY(int stateLaserPosition READ stateLaserPosition WRITE setStateLaserPosition NOTIFY stateLaserPositionChanged)
    Q_PROPERTY(int stateAngularRateControl READ stateAngularRateControl WRITE setStateAngularRateControl NOTIFY stateAngularRateControlChanged)
    Q_PROPERTY(int stateAttitudeStabilization READ stateAttitudeStabilization WRITE setStateAttitudeStabilization NOTIFY stateAttitudeStabilizationChanged)
    Q_PROPERTY(int stateYawControl READ stateYawControl WRITE setStateYawControl NOTIFY stateYawControlChanged)
    Q_PROPERTY(int stateZControl READ stateZControl WRITE setStateZControl NOTIFY stateZControlChanged)
    Q_PROPERTY(int stateXYControl READ stateXYControl WRITE setStateXYControl NOTIFY stateXYControlChanged)
    Q_PROPERTY(int stateMotorOut READ stateMotorOut WRITE setStateMotorOut NOTIFY stateMotorOutChanged)
    Q_PROPERTY(int stateRC READ stateRC WRITE setStateRC NOTIFY stateRCChanged)
    Q_PROPERTY(int stateGeoFence READ stateGeoFence WRITE setStateGeoFence NOTIFY stateGeoFenceChanged)
    Q_PROPERTY(int stateAHRS READ stateAHRS WRITE setStateAHRS NOTIFY stateAHRSChanged)
    Q_PROPERTY(int stateTerrain READ stateTerrain WRITE setStateTerrain NOTIFY stateTerrainChanged)
    Q_PROPERTY(int stateReverseMotor READ stateReverseMotor WRITE setStateReverseMotor NOTIFY stateReverseMotorChanged)
    Q_PROPERTY(int stateLogging READ stateLogging WRITE setStateLogging NOTIFY stateLoggingChanged)
    Q_PROPERTY(int stateBattery READ stateBattery WRITE setStateBattery NOTIFY stateBatteryChanged)
    Q_PROPERTY(int stateProximity READ stateProximity WRITE setStateProximity NOTIFY stateProximityChanged)
    Q_PROPERTY(int stateSatCom READ stateSatCom WRITE setStateSatCom NOTIFY stateSatComChanged)
    Q_PROPERTY(int stateObstacleAviodance READ stateObstacleAviodance WRITE setStateObstacleAviodance NOTIFY stateObstacleAviodanceChanged)
    Q_PROPERTY(int statePropulsion READ statePropulsion WRITE setStatePropulsion NOTIFY statePropulsionChanged)

public:
    enum State {
        SENSOR_NOT_PRESENT,
        SENSOR_ERROR,
        SENSOR_READY
    };
    Q_ENUM(State)

    Failsafe(QObject *parent = nullptr);
    explicit Failsafe(DataStreamer *streamer, QObject *parent = nullptr);

    int stateGyros() const;

    int stateAccels() const;
    void setStateAccels(int newStateAccels);

    int stateMagnetometer() const;
    void setStateMagnetometer(int newStateMagnetometer);

    int stateAbsPressure() const;
    void setStateAbsPressure(int newStateAbsPressure);

    int stateDiffPressure() const;
    void setStateDiffPressure(int newStateDiffPressure);

    int stateGPS() const;
    void setStateGPS(int newStateGPS);

    int stateOpticalFlow() const;
    void setStateOpticalFlow(int newStateOpticalFlow);

    int stateVisionPosition() const;
    void setStateVisionPosition(int newStateVisionPosition);

    int stateLaserPosition() const;
    void setStateLaserPosition(int newStateLaserPosition);

    int stateAngularRateControl() const;
    void setStateAngularRateControl(int newStateAngularRateControl);

    int stateAttitudeStabilization() const;
    void setStateAttitudeStabilization(int newStateAttitudeStabilization);

    int stateYawControl() const;
    void setStateYawControl(int newStateYawControl);

    int stateZControl() const;
    void setStateZControl(int newStateZControl);

    int stateXYControl() const;
    void setStateXYControl(int newStateXYControl);

    int stateMotorOut() const;
    void setStateMotorOut(int newStateMotorOut);

    int stateRC() const;
    void setStateRC(int newStateRC);

    int stateGeoFence() const;
    void setStateGeoFence(int newStateGeoFence);

    int stateAHRS() const;
    void setStateAHRS(int newStateAHRS);

    int stateTerrain() const;
    void setStateTerrain(int newStateTerrain);

    int stateReverseMotor() const;
    void setStateReverseMotor(int newStateReverseMotor);

    int stateLogging() const;
    void setStateLogging(int newStateLogging);

    int stateBattery() const;
    void setStateBattery(int newStateBattery);

    int stateProximity() const;
    void setStateProximity(int newStateProximity);

    int stateSatCom() const;
    void setStateSatCom(int newStateSatCom);

    int stateObstacleAviodance() const;
    void setStateObstacleAviodance(int newStateObstacleAviodance);

    int statePropulsion() const;
    void setStatePropulsion(int newStatePropulsion);

public slots:
    void setStateGyros(int newStateGyros);

signals:

    void stateChanged();
    void stateGyrosChanged();
    void stateAccelsChanged();
    void stateMagnetometerChanged();
    void stateAbsPressureChanged();
    void stateDiffPressureChanged();
    void stateGPSChanged();
    void stateOpticalFlowChanged();
    void stateVisionPositionChanged();
    void stateLaserPositionChanged();
    void stateAngularRateControlChanged();
    void stateAttitudeStabilizationChanged();
    void stateYawControlChanged();
    void stateZControlChanged();
    void stateXYControlChanged();
    void stateMotorOutChanged();
    void stateRCChanged();
    void stateGeoFenceChanged();
    void stateAHRSChanged();
    void stateTerrainChanged();
    void stateReverseMotorChanged();
    void stateLoggingChanged();
    void stateBatteryChanged();
    void stateProximityChanged();
    void stateSatComChanged();
    void stateObstacleAviodanceChanged();
    void statePropulsionChanged();

private:
    int m_stateGyros;
    int m_stateAccels;
    int m_stateMagnetometer;
    int m_stateAbsPressure;
    int m_stateDiffPressure;
    int m_stateGPS;
    int m_stateOpticalFlow;
    int m_stateVisionPosition;
    int m_stateLaserPosition;
    int m_stateAngularRateControl;
    int m_stateAttitudeStabilization;
    int m_stateYawControl;
    int m_stateZControl;
    int m_stateXYControl;
    int m_stateMotorOut;
    int m_stateRC;
    int m_stateGeoFence;
    int m_stateAHRS;
    int m_stateTerrain;
    int m_stateReverseMotor;
    int m_stateLogging;
    int m_stateBattery;
    int m_stateProximity;
    int m_stateSatCom;
    int m_stateObstacleAviodance;
    int m_statePropulsion;
};

#endif // FAILSAFE_H
