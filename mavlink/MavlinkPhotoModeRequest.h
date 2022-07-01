#ifndef MAVLINKPHOTOMODEREQUEST_H
#define MAVLINKPHOTOMODEREQUEST_H
#include "../streamer/PhotoModeRequest.h"
#include "MavlinkRequest.h"
#include <QObject>
#include <QDebug>

class MavlinkPhotoModeRequest : public PhotoModeRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkPhotoModeRequest(float time, float dst, QObject *parent = nullptr);
    virtual ~MavlinkPhotoModeRequest() = default;
    virtual bool ready() override;

protected:
    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

};

#endif // MAVLINKPHOTOMODEREQUEST_H
