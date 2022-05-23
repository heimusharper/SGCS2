#ifndef MAVLINKSTREAM_H
#define MAVLINKSTREAM_H

#include <chrono>
#include "ModeHelper.h"

class MavlinkStream
{
public:

protected:

    virtual bool processMessage(const mavlink_message_t &msg) = 0;
    virtual void onInit() {

    }

    uint8_t GCSID;
    uint8_t COMPID;
    uint8_t APID;
    uint8_t APCOMP;
    ModeHelper::APMode m_apMode = ModeHelper::APMode::UNDEFIEND;

public:
    /*!
     * \brief MavlinkRequest
     */
    MavlinkStream()
    {
    }
    virtual ~MavlinkStream() = default;
    /*!
     * \brief init определить оснвные параметры
     * \param gcsid ИД ПО
     * \param compid ИД компонента ПО
     * \param apid ИД принимающего
     * \param apcomp ИД принимающего компонента
     */
    void init(uint8_t gcsid, uint8_t compid, uint8_t apid, uint8_t apcomp, ModeHelper::APMode mode) {
        GCSID = gcsid;
        COMPID = compid;
        APID = apid;
        APCOMP = apcomp;
        m_apMode = mode;
        onInit();
    }
    /*!
     * \brief responce получена некоторая посылка
     * \param msg посылка
     */
    void responce(const mavlink_message_t &msg)  {
        processMessage(msg);
    }
};


#endif // MAVLINKSTREAM_H
