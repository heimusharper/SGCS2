#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>
#include "ConnectionType.h"
#include <QSerialPort>
#include <QDebug>
#include <QTimer>
#include <QQueue>
#include <QThread>

class SerialConnectionWorker : public QObject
{
    Q_OBJECT
public:
    SerialConnectionWorker(const QString &port);
    ~SerialConnectionWorker();

signals:

    void doWrite(const QByteArray &data);
    void onRead(const QByteArray &data);
    void isConnected(bool l);
    void onFailed(const QString &failMsg);

public slots:

    void run();

private slots:

    void tick();

    void onReadyData();

    void doWriteImpl(const QByteArray &data);

private:
    QString m_port;
    QSerialPort *m_serial = nullptr;
    QTimer *m_timer = nullptr;
    QQueue<QByteArray> m_buffer;
    QByteArray outBuffer;

    bool m_connectionState = false;
};

class SerialConnection : public ConnectionType
{
    Q_OBJECT
public:
    explicit SerialConnection(const QString &port, QObject *parent = nullptr);
    virtual ~SerialConnection();
    virtual void connectTo() override;

public slots:

    virtual void doWriteData(const QByteArray &data) override;
private:

    SerialConnectionWorker *m_serialPort = nullptr;
    QThread *m_thread = nullptr;


};

#endif // SERIALCONNECTION_H
