#ifndef MAVLINKMAINDATASTREAM_H
#define MAVLINKMAINDATASTREAM_H

#include <QObject>
#include "../streamer/MainDataStream.h"
#include "MavlinkStream.h"
/*!
 * \brief The MavlinkMainDataStream class
 *
 * Detect flight modes and UAV type
 */
class MavlinkMainDataStream : public MainDataStream, public MavlinkStream
{
    Q_OBJECT
public:
    explicit MavlinkMainDataStream(QObject *parent = nullptr);
    virtual ~MavlinkMainDataStream() = default;
private:

    int convertUAVType(int t) const;

    bool m_apInitiated = false;
    int m_lastUavType = -1;

    bool m_isFlight = false;

signals:
    void onFoundAutopilot(uint8_t sysid, uint8_t compid, ModeHelper::APMode mode);

protected:

    enum ARM_PROCESS {
        ARM,
        TAKEOFF,
        NONE
    };

    ARM_PROCESS m_armProcess = ARM_PROCESS::NONE;

    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

};

#endif // MAVLINKMAINDATASTREAM_H
