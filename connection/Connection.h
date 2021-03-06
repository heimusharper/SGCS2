#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "ConnectionType.h"

class Connection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
public:
    explicit Connection(QObject *parent = nullptr);

    bool connected() const;

    Q_INVOKABLE void disconnectFrom();
    Q_INVOKABLE void connectToUDP(const QString &host, int port);
    Q_INVOKABLE void connectToUART(const QString &port);

public slots:
    void setConnected(bool newConnected);
    void writeData(const QByteArray &data);

signals:

    void connectedChanged();
    void onReadyData(const QByteArray &data);

private:
    bool m_connected = false;

    ConnectionType *m_connection = nullptr;
};

#endif // CONNECTION_H
