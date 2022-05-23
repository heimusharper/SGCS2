#include "Sensors.h"

Sensors::Sensors(QObject *parent)
    : QObject{parent}
{
    qDebug() << "USe wrong contructor";
}

Sensors::Sensors(DataStreamer *streamer, QObject *parent)
    : QObject{parent},
    m_streamer(streamer)
{
    SensorsDataStream *sensorsStreamer = m_streamer->getSensorsStream();
    connect(sensorsStreamer, &SensorsDataStream::onGPSStateChanged, this, &Sensors::setGpsStatus);
}

int Sensors::gpsStatus() const
{
    return m_gpsStatus;
}

void Sensors::setGpsStatus(int newGpsStatus)
{
    if (m_gpsStatus == newGpsStatus)
        return;
    m_gpsStatus = newGpsStatus;
    emit gpsStatusChanged();
}
