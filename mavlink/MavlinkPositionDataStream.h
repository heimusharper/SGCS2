#ifndef MAVLINKPOSITIONDATASTREAM_H
#define MAVLINKPOSITIONDATASTREAM_H
#include "../streamer/PositionDataStream.h"
#include "MavlinkStream.h"
#include <QDebug>

class MavlinkPositionDataStream : public PositionDataStream, public MavlinkStream
{
    Q_OBJECT
public:
    MavlinkPositionDataStream(QObject *parent);
    virtual ~MavlinkPositionDataStream() = default;

protected:
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;
};

#endif // MAVLINKPOSITIONDATASTREAM_H
