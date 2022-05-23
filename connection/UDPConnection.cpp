#include "UDPConnection.h"

UDPConnection::UDPConnection(const QString &host, int port, QObject *parent)
    : ConnectionType{parent},
    m_host(host),
    m_port(port)
{
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::errorOccurred, this, [this](){
        QString err =  m_socket->errorString();
        qDebug() << "LAST ERR " << err;
        emit connectionFailure(err);
        emit isConnected(false);
        if (m_isHasData)
        {
            QTimer::singleShot(500, this, &UDPConnection::connectTo);
        }
    });
    connect(m_socket, &QUdpSocket::readyRead, this, [this](){
        auto s = m_socket->pendingDatagramSize();
        if (s > 0) {
            if (!m_isHasData) {
                emit isConnected(true);
                m_isHasData = true;
            }
            QByteArray data;
            data.resize(s);
            m_socket->readDatagram(data.data(), s);
            emit onReadyData(data);
            // qDebug() << "READD" << s << data.toHex();
        }
    });

}

UDPConnection::~UDPConnection()
{
}

void UDPConnection::connectTo()
{
    m_isHasData = false;
    m_socket->bind(QHostAddress(m_host), m_port);
}
