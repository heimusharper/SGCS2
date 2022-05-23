#ifndef MAVLINKSENSORSTREAM_H
#define MAVLINKSENSORSTREAM_H

#include "../streamer/SensorsDataStream.h"
#include <QObject>
#include "MavlinkStream.h"

class MavlinkSensorsDataStream : public SensorsDataStream, public MavlinkStream
{
    Q_OBJECT
public:
    explicit MavlinkSensorsDataStream(QObject *parent = nullptr);
    virtual ~MavlinkSensorsDataStream() = default;
private:
    int fixType = GPS_FIX_TYPE_NO_GPS;
protected:
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

};

#endif // MAVLINKSENSORSTREAM_H
