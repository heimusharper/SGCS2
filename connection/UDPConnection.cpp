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
            // QHostAddress cliAddr;
            // uint16_t port;
            m_socket->readDatagram(data.data(), s, &m_userHost, &m_userPort);
            emit onReadyData(data);
            // qDebug() << "READD" << s << data.toHex() << cliAddr.toString() << " p " << port;
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

void UDPConnection::doWriteData(const QByteArray &data)
{
    qDebug() << "WRITE" << data.toHex();
    // m_socket->write(data);
    m_socket->writeDatagram(data, m_userHost, m_userPort);
}
