#ifndef MAVLINKSTREAMER_H
#define MAVLINKSTREAMER_H

#include <QObject>
#include "../streamer/DataStreamer.h"
#include <QTimer>
#include <QDebug>

// streamers
#include "MavlinkRequest.h"
#include "MavlinkPositionDataStream.h"
#include "MavlinkHomePositionRequest.h"
#include "MavlinkSensorsDataStream.h"
#include "MavlinkMainDataStream.h"
#include "MavlinkARMRequest.h"
#include "MavlinkPingRequest.h"
#include "MavlinkManualControlRequest.h"
#include "MavlinkMissionReadRequest.h"
#include "MavlinkPhotoModeRequest.h"
#include "MavlinkPhotoPayloadStream.h"

class MavlinkStreamer : public DataStreamer
{
    Q_OBJECT
public:
    explicit MavlinkStreamer(QObject *parent = nullptr);
    virtual ~MavlinkStreamer();

    virtual PositionDataStream *getPositionDataStream() override;
    virtual SensorsDataStream *getSensorsStream() override;
    virtual MainDataStream *getMainStream() override;

    virtual HomePositionRequest *createHomePositionRequest() override;
    virtual ARMRequest *createARMRequest(ARMRequest::Mode mode) override;
    virtual ManualControlRequest *createManualControlRequest() override;
    virtual MissionReadRequest *createMissionReadRequest() override;
    virtual PhotoModeRequest *createPhotoModeRequest(float time, float dst) override;
    virtual PhotoPayloadStream *getPhotoPayloadStream() override;

public slots:

    virtual void onDataReceived(const QByteArray &data) override;
private:
    uint8_t MAVLINK_CHANEL = 0;
    uint8_t GCS_ID = 255;//MAV_AUTOPILOT_ARDUPILOTMEGA;
    uint8_t GCS_COMPID = MAV_COMP_ID_MISSIONPLANNER;
    bool m_initiated = false;
    uint8_t AP_ID = 1;
    uint8_t AP_COMPID = 1;
    ModeHelper::APMode AP_MODE = ModeHelper::PIXHAWK;

    MavlinkMainDataStream *m_mainDataStream = nullptr;
    MavlinkPositionDataStream *m_positionDataStream = nullptr;
    MavlinkSensorsDataStream *m_sensorsDataStream = nullptr;

    MavlinkHomePositionRequest *m_homePositionRequest = nullptr;
    MavlinkARMRequest *m_armRequest = nullptr;
    MavlinkPingRequest *m_pingRequest = nullptr;
    MavlinkManualControlRequest *m_manualControlRequest = nullptr;
    MavlinkMissionReadRequest *m_missionReadRequest = nullptr;
    MavlinkPhotoModeRequest *m_photoModeRequest = nullptr;
    MavlinkPhotoPayloadStream *m_photoPayloadStream = nullptr;



    QTimer *m_ioTimer = nullptr;
    void tryWriteData();
    void transmit(const mavlink_message_t &msg);

signals:

};

#endif // MAVLINKSTREAMER_H
