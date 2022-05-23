#ifndef MAVLINKSTREAMER_H
#define MAVLINKSTREAMER_H

#include <QObject>
#include "../streamer/DataStreamer.h"

// streamers
#include "MavlinkRequest.h"
#include "MavlinkMainDataStream.h"
#include "MavlinkPositionDataStream.h"
#include "MavlinkHomePositionRequest.h"
#include "MavlinkSensorsDataStream.h"

class MavlinkStreamer : public DataStreamer
{
    Q_OBJECT
public:
    explicit MavlinkStreamer(QObject *parent = nullptr);
    virtual ~MavlinkStreamer();

    virtual PositionDataStream *getPositionDataStream() override;
    virtual SensorsDataStream *getSensorsStream() override;
    virtual HomePositionRequest *createHomePositionRequest() override;
    virtual MainDataStream *getMainStream() override;

public slots:

    virtual void onDataReceived(const QByteArray &data) override;
private:
    uint8_t MAVLINK_CHANEL = 0;
    uint8_t GCS_ID = MAV_AUTOPILOT_ARDUPILOTMEGA;
    uint8_t GCS_COMPID = 1;
    bool m_initiated = false;
    uint8_t AP_ID = 1;
    uint8_t AP_COMPID = 1;
    ModeHelper::APMode AP_MODE = ModeHelper::PIXHAWK;

    MavlinkHomePositionRequest *m_homePositionRequest = nullptr;

    MavlinkMainDataStream *m_mainDataStream = nullptr;
    MavlinkPositionDataStream *m_positionDataStream = nullptr;
    MavlinkSensorsDataStream *m_sensorsDataStream = nullptr;

signals:

};

#endif // MAVLINKSTREAMER_H
