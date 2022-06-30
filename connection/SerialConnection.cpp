#include "SerialConnection.h"

SerialConnection::SerialConnection(const QString &port, QObject *parent)
    : ConnectionType{parent}
{
    m_serialPort = new SerialConnectionWorker(port);
    m_thread = new QThread();
    connect(m_thread, &QThread::started, m_serialPort, &SerialConnectionWorker::run);
    connect(m_thread, &QThread::destroyed, m_serialPort, &SerialConnectionWorker::deleteLater);
    connect(m_serialPort, &SerialConnectionWorker::onRead, this, &SerialConnection::onReadyData);
    connect(m_serialPort, &SerialConnectionWorker::isConnected, this, &SerialConnection::isConnected);
    connect(m_serialPort, &SerialConnectionWorker::onFailed, this, &SerialConnection::connectionFailure);
    m_serialPort->moveToThread(m_thread);
    m_thread->start();
}

SerialConnection::~SerialConnection()
{
    if (m_thread) {
        m_thread->terminate();
        m_thread->wait();
        m_thread->deleteLater();
    }
}

void SerialConnection::connectTo()
{

}

void SerialConnection::doWriteData(const QByteArray &data)
{
    emit m_serialPort->doWrite(data);
}

// w

SerialConnectionWorker::SerialConnectionWorker(const QString &port)
    : m_port(port)
{
}

SerialConnectionWorker::~SerialConnectionWorker() {
    if (m_serial) {
        m_timer->stop();
        m_timer->deleteLater();
        if (m_serial->isOpen()) {
            m_serial->close();
            m_serial->deleteLater();
        }
    }
}

void SerialConnectionWorker::run()
{
    outBuffer.reserve(128);
    m_buffer.reserve(30);
    connect(this, &SerialConnectionWorker::doWrite, this, &SerialConnectionWorker::doWriteImpl);
    m_serial = new QSerialPort();
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &SerialConnectionWorker::tick);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialConnectionWorker::onReadyData);
    m_timer->start(500);
}

void SerialConnectionWorker::tick()
{
    if (m_serial->isOpen()) {
        if (m_buffer.empty())
            return;
        QByteArray data = m_buffer.dequeue();
        m_serial->write(data);
        m_serial->waitForBytesWritten();
    } else {
        if (m_connectionState)
            emit isConnected(false);
        m_connectionState = false;
        m_timer->setInterval(500);
        m_serial->setPortName(m_port);
        m_serial->setBaudRate(57600);
        m_serial->setDataBits(QSerialPort::Data8);
        m_serial->setFlowControl(QSerialPort::NoFlowControl);
        m_serial->setParity(QSerialPort::NoParity);
        m_serial->setStopBits(QSerialPort::OneStop);
        if (m_serial->open(QIODevice::ReadWrite)) {
            m_timer->setInterval(20);
            emit isConnected(true);
            m_connectionState = true;
        } else {
            emit onFailed(m_serial->errorString());
        }
    }
}

void SerialConnectionWorker::onReadyData()
{
    QByteArray data = m_serial->readAll();
    outBuffer.append(data);
    if (outBuffer.size() > 32)
    {
        qDebug() << "buffer " << outBuffer.toHex();
        emit onRead(outBuffer);
        outBuffer.clear();
    }
}

void SerialConnectionWorker::doWriteImpl(const QByteArray &data)
{
    m_buffer.enqueue(data);
    if (m_buffer.size() > 30)
        m_buffer.dequeue();
}
