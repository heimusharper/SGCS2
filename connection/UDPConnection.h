#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <QObject>
#include "ConnectionType.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTimer>

class UDPConnection : public ConnectionType
{
    Q_OBJECT
public:
    explicit UDPConnection(const QString &host, int port, QObject *parent = nullptr);
    virtual ~UDPConnection();
    virtual void connectTo() override;

public slots:

    virtual void doWriteData(const QByteArray &data) override;
private:

    const QString m_host;
    const int m_port;

    QUdpSocket *m_socket;
    bool m_isHasData = false;

    QHostAddress m_userHost;
    uint16_t m_userPort;

signals:

};

#endif // UDPCONNECTION_H
