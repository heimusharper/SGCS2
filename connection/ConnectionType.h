#ifndef CONNECTIONTYPE_H
#define CONNECTIONTYPE_H

#include <QObject>

class ConnectionType : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionType(QObject *parent = nullptr);
    virtual void connectTo() = 0;

signals:

    void isConnected(bool connected);
    void connectionFailure(const QString &error);
    void onReadyData(const QByteArray &data);

};

#endif // CONNECTIONTYPE_H
