#include "Connection.h"

Connection::Connection(QObject *parent)
    : QObject{parent}
{

}

bool Connection::connected() const
{
    return m_connected;
}

void Connection::setConnected(bool newConnected)
{
    if (m_connected == newConnected)
        return;
    m_connected = newConnected;
    emit connectedChanged();
}

void Connection::writeData(const QByteArray &data)
{
    if (m_connected && m_connection) {
        m_connection->doWriteData(data);
    }
}

void Connection::disconnectFrom()
{
    if (m_connection) {
        m_connection->deleteLater();
        m_connection = nullptr;
    }
    setConnected(false);
}

void Connection::connectToUDP(const QString &host, int port)
{
    disconnectFrom();
    m_connection = new UDPConnection(host, port, this);
    connect(m_connection, &ConnectionType::isConnected, this, &Connection::setConnected);
    connect(m_connection, &ConnectionType::onReadyData, this, &Connection::onReadyData);

    m_connection->connectTo();
}
