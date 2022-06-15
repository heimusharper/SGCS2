#ifndef MAVLINKREQUEST_H
#define MAVLINKREQUEST_H

#include <chrono>
#include "MavlinkStream.h"
#include "ModeHelper.h"

class MavlinkRequest
{

protected:

    enum class MessageError : int {
        MESSAGE_TIMEOUT
    };

    virtual mavlink_message_t construct() = 0;
    virtual bool processMessage(const mavlink_message_t &msg) = 0;
    virtual void onInit() {

    }
    virtual void onError(const MavlinkRequest::MessageError error) {

    }

    uint8_t GCSID = 255;
    uint8_t COMPID = MAV_COMP_ID_MISSIONPLANNER;
    uint8_t APID = 0;
    uint8_t APCOMP = 0;
    ModeHelper::APMode APMODE;
    /*!
     * \brief m_maxMessageLiveTimeMs максимальное время жизни запроса
     * 0 - для одиночных
     * UINT32_MAX - для бесконечных
     * 1000 - по умолчанию
     */
    uint32_t m_maxMessageLiveTimeMs;
    uint32_t m_messageIntervalMs;
public:
    /*!
     * \brief MavlinkRequest
     */
    MavlinkRequest()
        : m_requestTime(std::chrono::system_clock::now()),
        m_dirty(true),
        m_empty(false),
        m_waitForMessage(true),
        m_maxMessageLiveTimeMs(-1),
        m_messageIntervalMs(500)
    {
        resetSignalValue();
    }
    virtual ~MavlinkRequest() = default;
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
        APMODE = mode;
        onInit();
    }
    /*!
     * \brief ready готовность посылки для отправки
     * \return true - готов
     * посылка может быть не готова в случе ожидания тамайута или
     * если не запланированна оправкта вовсе
     */
    virtual bool ready() {
        if (m_empty)
            return false;
        if (m_dirty)
            return true;
        if (m_waitForMessage) {
            const auto end = std::chrono::system_clock::now();
            if (m_maxMessageLiveTimeMs > 0 && m_maxMessageLiveTimeMs < UINT32_MAX) {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(end - m_firstRequestTime).count() > m_maxMessageLiveTimeMs) {
                    m_waitForMessage = false;
                    m_empty = true; // stop
                    onError(MavlinkRequest::MessageError::MESSAGE_TIMEOUT);
                    return false;
                }
            }
            if (std::chrono::duration_cast<std::chrono::milliseconds>(end - m_requestTime).count() > m_messageIntervalMs)
                return true;
        }
        return false;
    }
    /*!
     * \brief request получить посылку для отправки
     * \return посылка
     */
    virtual mavlink_message_t request() final {
        m_requestTime = std::chrono::system_clock::now();
        if (m_dirty) {
            m_firstRequestTime = m_requestTime;
            m_dirty = false;
            if (m_maxMessageLiveTimeMs == 0)
                m_waitForMessage = false;
        }
        m_requestsCount++;
        return construct();
    }
    /*!
     * \brief resetSignalValue сброс данных о качестве связи
     */
    void resetSignalValue()
    {
        m_requestsCount = 0;
        m_responsesCount = 0;
    }
    /*!
     * \brief signalValue сигнал
     * \return -1 - нельзя определить, иначе уровень качества в диапазоне [0, 1]
     */
    virtual float signalValue()
    {
        if (m_requestsCount < 1)
            return -1.f;
        return m_responsesCount / m_requestsCount;
    }
    /*!
     * \brief responce получена некоторая посылка
     * \param msg посылка
     */
    void responce(const mavlink_message_t &msg)  {
        if (processMessage(msg)) {
            if (m_maxMessageLiveTimeMs != UINT32_MAX)
                m_waitForMessage = false;
            m_responsesCount++;
        }
    }
protected:
    bool m_empty;
private:
    /*!
     * \brief m_requestsCount кол-во отправок
     */
    int m_requestsCount;
    /*!
     * \brief m_responsesCount кол-во принятых
     */
    int m_responsesCount;
    /*!
     * \brief m_dirty помощ для отправки, будет игнорировать таймаут для первого сообщения
     */
    bool m_dirty;
    /*!
     * \brief m_waitForMessage находинтся в процессе ожидания соощения
     */
    bool m_waitForMessage;
    /*!
     * \brief m_requestTime последний момент отправки сообщения
     */
    std::chrono::time_point<std::chrono::system_clock> m_requestTime;
    /*!
     * \brief m_firstRequestTime первый момент отправки сообщения
     */
    std::chrono::time_point<std::chrono::system_clock> m_firstRequestTime;
};

#endif // MAVLINKREQUEST_H
