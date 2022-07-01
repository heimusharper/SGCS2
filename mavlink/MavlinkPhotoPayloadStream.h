#ifndef MAVLINKPHOTOPAYLOADSTREAM_H
#define MAVLINKPHOTOPAYLOADSTREAM_H

#include "../streamer/PhotoPayloadStream.h"
#include <QObject>
#include "MavlinkRequest.h"
#include <QDebug>

class MavlinkPhotoPayloadStream : public PhotoPayloadStream, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkPhotoPayloadStream(QObject *parent = nullptr);
    virtual ~MavlinkPhotoPayloadStream();

    virtual bool ready() override;
    virtual void takeOneShot() override;
protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    bool m_waitForTakeOneShot = false;
};



#endif // MAVLINKPHOTOPAYLOADSTREAM_H
