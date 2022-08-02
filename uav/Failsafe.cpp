#include "Failsafe.h"

Failsafe::Failsafe(QObject *parent)
    : QObject{parent}
{
}

Failsafe::Failsafe(DataStreamer *streamer, QObject *parent)
    : QObject{parent}
{
    ErrorStreamer *errs = streamer->getErrorStream();
    connect(errs, &ErrorStreamer::onStatesChenged, this, [this](const ErrorStreamer::States &state){
        auto convert = [](const ErrorStreamer::States::State s){
            switch (s) {
                case ErrorStreamer::States::State::ERROR:
                    return State::SENSOR_ERROR;
                case ErrorStreamer::States::State::READY:
                    return State::SENSOR_READY;
                default:
                    break;
            }
            return State::SENSOR_NOT_PRESENT;
        };
        setStateGyros(convert(state.gyro));
        setStateAccels(convert(state.accel));
        setStateMagnetometer(convert(state.mag));
        setStateAbsPressure(convert(state.absPressure));
        setStateDiffPressure(convert(state.diffPressure));
        setStateGPS(convert(state.gps));
        setStateOpticalFlow(convert(state.opticalFlow));
        setStateVisionPosition(convert(state.visionPosition));
        setStateLaserPosition(convert(state.laserPosition));
        setStateAngularRateControl(convert(state.angularRateControl));
        setStateAttitudeStabilization(convert(state.attitudeStablization));
        setStateYawControl(convert(state.yawControl));
        setStateZControl(convert(state.zControl));
        setStateXYControl(convert(state.xyControl));
        setStateMotorOut(convert(state.motorOut));
        setStateRC(convert(state.rc));
        setStateGeoFence(convert(state.geoFence));
        setStateAHRS(convert(state.ahrs));
        setStateTerrain(convert(state.terrain));
        setStateReverseMotor(convert(state.reverseMotor));
        setStateLogging(convert(state.log));
        setStateBattery(convert(state.battery));
        setStateProximity(convert(state.proximity));
        setStateSatCom(convert(state.satcom));
        setStateObstacleAviodance(convert(state.obstacleAviodance));
        setStatePropulsion(convert(state.propulsion));
        emit stateChanged();
    });
}

int Failsafe::stateGyros() const
{
    return m_stateGyros;
}

void Failsafe::setStateGyros(int newStateGyros)
{
    if (m_stateGyros == newStateGyros)
        return;
    m_stateGyros = newStateGyros;
    emit stateGyrosChanged();
}

int Failsafe::stateAccels() const
{
    return m_stateAccels;
}

void Failsafe::setStateAccels(int newStateAccels)
{
    if (m_stateAccels == newStateAccels)
        return;
    m_stateAccels = newStateAccels;
    emit stateAccelsChanged();
}

int Failsafe::stateMagnetometer() const
{
    return m_stateMagnetometer;
}

void Failsafe::setStateMagnetometer(int newStateMagnetometer)
{
    if (m_stateMagnetometer == newStateMagnetometer)
        return;
    m_stateMagnetometer = newStateMagnetometer;
    emit stateMagnetometerChanged();
}

int Failsafe::stateAbsPressure() const
{
    return m_stateAbsPressure;
}

void Failsafe::setStateAbsPressure(int newStateAbsPressure)
{
    if (m_stateAbsPressure == newStateAbsPressure)
        return;
    m_stateAbsPressure = newStateAbsPressure;
    emit stateAbsPressureChanged();
}

int Failsafe::stateDiffPressure() const
{
    return m_stateDiffPressure;
}

void Failsafe::setStateDiffPressure(int newStateDiffPressure)
{
    if (m_stateDiffPressure == newStateDiffPressure)
        return;
    m_stateDiffPressure = newStateDiffPressure;
    emit stateDiffPressureChanged();
}

int Failsafe::stateGPS() const
{
    return m_stateGPS;
}

void Failsafe::setStateGPS(int newStateGPS)
{
    if (m_stateGPS == newStateGPS)
        return;
    m_stateGPS = newStateGPS;
    emit stateGPSChanged();
}

int Failsafe::stateOpticalFlow() const
{
    return m_stateOpticalFlow;
}

void Failsafe::setStateOpticalFlow(int newStateOpticalFlow)
{
    if (m_stateOpticalFlow == newStateOpticalFlow)
        return;
    m_stateOpticalFlow = newStateOpticalFlow;
    emit stateOpticalFlowChanged();
}

int Failsafe::stateVisionPosition() const
{
    return m_stateVisionPosition;
}

void Failsafe::setStateVisionPosition(int newStateVisionPosition)
{
    if (m_stateVisionPosition == newStateVisionPosition)
        return;
    m_stateVisionPosition = newStateVisionPosition;
    emit stateVisionPositionChanged();
}

int Failsafe::stateLaserPosition() const
{
    return m_stateLaserPosition;
}

void Failsafe::setStateLaserPosition(int newStateLaserPosition)
{
    if (m_stateLaserPosition == newStateLaserPosition)
        return;
    m_stateLaserPosition = newStateLaserPosition;
    emit stateLaserPositionChanged();
}

int Failsafe::stateAngularRateControl() const
{
    return m_stateAngularRateControl;
}

void Failsafe::setStateAngularRateControl(int newStateAngularRateControl)
{
    if (m_stateAngularRateControl == newStateAngularRateControl)
        return;
    m_stateAngularRateControl = newStateAngularRateControl;
    emit stateAngularRateControlChanged();
}

int Failsafe::stateAttitudeStabilization() const
{
    return m_stateAttitudeStabilization;
}

void Failsafe::setStateAttitudeStabilization(int newStateAttitudeStabilization)
{
    if (m_stateAttitudeStabilization == newStateAttitudeStabilization)
        return;
    m_stateAttitudeStabilization = newStateAttitudeStabilization;
    emit stateAttitudeStabilizationChanged();
}

int Failsafe::stateYawControl() const
{
    return m_stateYawControl;
}

void Failsafe::setStateYawControl(int newStateYawControl)
{
    if (m_stateYawControl == newStateYawControl)
        return;
    m_stateYawControl = newStateYawControl;
    emit stateYawControlChanged();
}

int Failsafe::stateZControl() const
{
    return m_stateZControl;
}

void Failsafe::setStateZControl(int newStateZControl)
{
    if (m_stateZControl == newStateZControl)
        return;
    m_stateZControl = newStateZControl;
    emit stateZControlChanged();
}

int Failsafe::stateXYControl() const
{
    return m_stateXYControl;
}

void Failsafe::setStateXYControl(int newStateXYControl)
{
    if (m_stateXYControl == newStateXYControl)
        return;
    m_stateXYControl = newStateXYControl;
    emit stateXYControlChanged();
}

int Failsafe::stateMotorOut() const
{
    return m_stateMotorOut;
}

void Failsafe::setStateMotorOut(int newStateMotorOut)
{
    if (m_stateMotorOut == newStateMotorOut)
        return;
    m_stateMotorOut = newStateMotorOut;
    emit stateMotorOutChanged();
}

int Failsafe::stateRC() const
{
    return m_stateRC;
}

void Failsafe::setStateRC(int newStateRC)
{
    if (m_stateRC == newStateRC)
        return;
    m_stateRC = newStateRC;
    emit stateRCChanged();
}

int Failsafe::stateGeoFence() const
{
    return m_stateGeoFence;
}

void Failsafe::setStateGeoFence(int newStateGeoFence)
{
    if (m_stateGeoFence == newStateGeoFence)
        return;
    m_stateGeoFence = newStateGeoFence;
    emit stateGeoFenceChanged();
}

int Failsafe::stateAHRS() const
{
    return m_stateAHRS;
}

void Failsafe::setStateAHRS(int newStateAHRS)
{
    if (m_stateAHRS == newStateAHRS)
        return;
    m_stateAHRS = newStateAHRS;
    emit stateAHRSChanged();
}

int Failsafe::stateTerrain() const
{
    return m_stateTerrain;
}

void Failsafe::setStateTerrain(int newStateTerrain)
{
    if (m_stateTerrain == newStateTerrain)
        return;
    m_stateTerrain = newStateTerrain;
    emit stateTerrainChanged();
}

int Failsafe::stateReverseMotor() const
{
    return m_stateReverseMotor;
}

void Failsafe::setStateReverseMotor(int newStateReverseMotor)
{
    if (m_stateReverseMotor == newStateReverseMotor)
        return;
    m_stateReverseMotor = newStateReverseMotor;
    emit stateReverseMotorChanged();
}

int Failsafe::stateLogging() const
{
    return m_stateLogging;
}

void Failsafe::setStateLogging(int newStateLogging)
{
    if (m_stateLogging == newStateLogging)
        return;
    m_stateLogging = newStateLogging;
    emit stateLoggingChanged();
}

int Failsafe::stateBattery() const
{
    return m_stateBattery;
}

void Failsafe::setStateBattery(int newStateBattery)
{
    if (m_stateBattery == newStateBattery)
        return;
    m_stateBattery = newStateBattery;
    emit stateBatteryChanged();
}

int Failsafe::stateProximity() const
{
    return m_stateProximity;
}

void Failsafe::setStateProximity(int newStateProximity)
{
    if (m_stateProximity == newStateProximity)
        return;
    m_stateProximity = newStateProximity;
    emit stateProximityChanged();
}

int Failsafe::stateSatCom() const
{
    return m_stateSatCom;
}

void Failsafe::setStateSatCom(int newStateSatCom)
{
    if (m_stateSatCom == newStateSatCom)
        return;
    m_stateSatCom = newStateSatCom;
    emit stateSatComChanged();
}

int Failsafe::stateObstacleAviodance() const
{
    return m_stateObstacleAviodance;
}

void Failsafe::setStateObstacleAviodance(int newStateObstacleAviodance)
{
    if (m_stateObstacleAviodance == newStateObstacleAviodance)
        return;
    m_stateObstacleAviodance = newStateObstacleAviodance;
    emit stateObstacleAviodanceChanged();
}

int Failsafe::statePropulsion() const
{
    return m_statePropulsion;
}

void Failsafe::setStatePropulsion(int newStatePropulsion)
{
    if (m_statePropulsion == newStatePropulsion)
        return;
    m_statePropulsion = newStatePropulsion;
    emit statePropulsionChanged();
}
