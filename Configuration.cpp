#include "Configuration.h"

Configuration::Configuration(QSettings *settings, QObject *parent)
    : QObject{parent}, m_settings(settings)
{
    m_mapProviderName = m_settings->value("map/provider_name", "googlemaps").toString();
    m_mapTypeName = m_settings->value("map/type_name", "Satelite").toString();
    m_streamLast = m_settings->value("stream/last_stream", "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4").toString();
    m_streamAutoConnect = m_settings->value("stream/autoconnect", true).toBool();

}

Configuration::~Configuration()
{
    m_settings->setValue("map/provider_name", m_mapProviderName);
    m_settings->setValue("map/type_name", m_mapTypeName);
    m_settings->setValue("stream/last_stream", m_streamLast);
    m_settings->setValue("stream/autoconnect", m_streamAutoConnect);


    m_settings->sync();
    m_settings->deleteLater();
}

const QString &Configuration::mapProviderName() const
{
    return m_mapProviderName;
}

void Configuration::setMapProviderName(const QString &newMapProviderName)
{
    if (m_mapProviderName == newMapProviderName)
        return;
    m_mapProviderName = newMapProviderName;
    emit mapProviderNameChanged();
}

const QString &Configuration::mapTypeName() const
{
    return m_mapTypeName;
}

void Configuration::setMapTypeName(const QString &newMapTypeName)
{
    if (m_mapTypeName == newMapTypeName)
        return;
    m_mapTypeName = newMapTypeName;
    emit mapTypeNameChanged();
}

const QString &Configuration::streamLast() const
{
    return m_streamLast;
}

void Configuration::setStreamLast(const QString &newLastStream)
{
    if (m_streamLast == newLastStream)
        return;
    m_streamLast = newLastStream;
    emit streamLastChanged();
}

bool Configuration::streamAutoConnect() const
{
    return m_streamAutoConnect;
}

void Configuration::setStreamAutoConnect(bool newStreamAutoConnect)
{
    if (m_streamAutoConnect == newStreamAutoConnect)
        return;
    m_streamAutoConnect = newStreamAutoConnect;
    emit streamAutoConnectChanged();
}
