#ifndef MAVLINKERRORSTREAM_H
#define MAVLINKERRORSTREAM_H

#include "../streamer/ErrorStreamer.h"
#include "MavlinkStream.h"
#include <QObject>

class MavlinkErrorStream : public ErrorStreamer, public MavlinkStream
{
    Q_OBJECT
public:

    explicit MavlinkErrorStream(QObject *parent = nullptr);
    virtual ~MavlinkErrorStream() = default;


protected:
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    States m_state;

signals:

};

#endif // MAVLINKERRORSTREAM_H
