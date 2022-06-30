#include "Configuration.h"

Configuration::Configuration(QSettings *settings, QObject *parent)
    : QObject{parent}, m_settings(settings)
{
    m_mapProviderName = m_settings->value("map/provider_name", "googlemaps").toString();
    m_mapTypeName = m_settings->value("map/type_name", "Satelite").toString();
    m_streamLast = m_settings->value("stream/last_stream", "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4").toString();
    m_streamAutoConnect = m_settings->value("stream/autoconnect", true).toBool();

    // connection
    m_connectionUDPHost = m_settings->value("connection/udp/host", QString("127.0.0.1")).toString();
    m_connectionUDPPort = m_settings->value("connection/udp/port", 14550).toInt();
#ifdef Q_OS_WIN
    m_connectionSerialPort = m_settings->value("connection/serial/port", QString("COM1")).toString();
#else
    m_connectionSerialPort = m_settings->value("connection/serial/port", QString("/dev/ttyUSB0")).toString();
#endif
    m_connectionMethod = m_settings->value("connection/method", "udp").toString();

}

Configuration::~Configuration()
{
    flush();
    m_settings->deleteLater();
}

void Configuration::flush()
{
    m_settings->setValue("map/provider_name", m_mapProviderName);
    m_settings->setValue("map/type_name", m_mapTypeName);
    m_settings->setValue("stream/last_stream", m_streamLast);
    m_settings->setValue("stream/autoconnect", m_streamAutoConnect);
    m_settings->setValue("connection/udp/host", m_connectionUDPHost);
    m_settings->setValue("connection/udp/port", m_connectionUDPPort);
    m_settings->setValue("connection/serial/port", m_connectionSerialPort);
    m_settings->setValue("connection/method", m_connectionMethod);

    m_settings->sync();
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

const QString &Configuration::connectionUDPHost() const
{
    return m_connectionUDPHost;
}

void Configuration::setConnectionUDPHost(const QString &newConnectionUDPHost)
{
    if (m_connectionUDPHost == newConnectionUDPHost)
        return;
    m_connectionUDPHost = newConnectionUDPHost;
    emit connectionUDPHostChanged();
}

int Configuration::connectionUDPPort() const
{
    return m_connectionUDPPort;
}

void Configuration::setConnectionUDPPort(int newConnectionUDPPort)
{
    if (m_connectionUDPPort == newConnectionUDPPort)
        return;
    m_connectionUDPPort = newConnectionUDPPort;
    emit connectionUDPPortChanged();
}

const QString &Configuration::connectionSerialPort() const
{
    return m_connectionSerialPort;
}

void Configuration::setConnectionSerialPort(const QString &newConnectionSerialPort)
{
    if (m_connectionSerialPort == newConnectionSerialPort)
        return;
    m_connectionSerialPort = newConnectionSerialPort;
    emit connectionSerialPortChanged();
}

const QString &Configuration::connectionMethod() const
{
    return m_connectionMethod;
}

void Configuration::setConnectionMethod(const QString &newConnectionMethod)
{
    if (m_connectionMethod == newConnectionMethod)
        return;
    m_connectionMethod = newConnectionMethod;
    emit connectionMethodChanged();
}
