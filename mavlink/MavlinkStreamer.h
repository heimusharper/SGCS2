#ifndef MAVLINKSTREAMER_H
#define MAVLINKSTREAMER_H

#include <QObject>
#include "../streamer/DataStreamer.h"

// streamers
#include "MavlinkRequest.h"
#include "MavlinkPositionDataStream.h"
#include "MavlinkHomePositionStreamer.h"

class MavlinkStreamer : public DataStreamer
{
    Q_OBJECT
public:
    explicit MavlinkStreamer(QObject *parent = nullptr);
    virtual ~MavlinkStreamer();

    virtual PositionDataStream *getPositionDataStream() override;
    virtual HomePositionRequest *createHomePositionRequest() override;
private:


    MavlinkHomePositionRequest *m_homePositionRequest = nullptr;

    QList<MavlinkRequest*> m_requests;

    PositionDataStream *m_positionDataStream = nullptr;

signals:

};

#endif // MAVLINKSTREAMER_H
