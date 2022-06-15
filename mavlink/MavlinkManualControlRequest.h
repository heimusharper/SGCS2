#ifndef MAVLINKMANUALCONTROLREQUEST_H
#define MAVLINKMANUALCONTROLREQUEST_H
#include "../streamer/ManualControlRequest.h"
#include "MavlinkRequest.h"
#include <QObject>
#include <chrono>
#include <QDebug>

class MavlinkManualControlRequest : public ManualControlRequest, public MavlinkRequest
{
    Q_OBJECT
public:
    explicit MavlinkManualControlRequest(QObject *parent = nullptr);
    virtual ~MavlinkManualControlRequest() = default;
    virtual bool ready() override;

    virtual void doLand() override;
    virtual void doRTL() override;
    virtual void doMission() override;

    virtual void goTo(const QGeoCoordinate &pos) override;

protected:
    void reset();

    enum class StateSet {
        UNDEFINED,
        RTL,
        GUIDED,
        SET_POSITION,
        MISSION,
        LAND
    };

    QGeoCoordinate m_targetPos;
    StateSet m_stateSet = StateSet::UNDEFINED;
    uint32_t m_bootTime = 0;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> m_lastBootMessage;

    bool m_isPositioning = false;

    virtual mavlink_message_t construct() override;
    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

};

#endif // MAVLINKMANUALCONTROLREQUEST_H
