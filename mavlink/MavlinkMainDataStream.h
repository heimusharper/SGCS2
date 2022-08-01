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

    // control mode controller
    bool m_isARMed = false;
    int m_controlMode = 0;
    uint8_t m_baseMode = 0;
    uint32_t m_customMode = 0;

signals:
    void onFoundAutopilot(uint8_t sysid, uint8_t compid, ModeHelper::APMode mode);

protected:

    virtual bool processMessage(const mavlink_message_t &msg) override;
    virtual void onInit() override;

    void checkMode();

};

#endif // MAVLINKMAINDATASTREAM_H
