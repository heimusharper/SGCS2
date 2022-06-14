#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QSettings>
#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mapProviderName READ mapProviderName WRITE setMapProviderName NOTIFY mapProviderNameChanged)
    Q_PROPERTY(QString mapTypeName READ mapTypeName WRITE setMapTypeName NOTIFY mapTypeNameChanged)
    Q_PROPERTY(QString streamLast READ streamLast WRITE setStreamLast NOTIFY streamLastChanged)
    Q_PROPERTY(bool streamAutoConnect READ streamAutoConnect WRITE setStreamAutoConnect NOTIFY streamAutoConnectChanged)

public:
    explicit Configuration(QSettings *settings, QObject *parent = nullptr);
    ~Configuration();

    const QString &mapProviderName() const;
    void setMapProviderName(const QString &newMapProviderName);

    const QString &mapTypeName() const;
    void setMapTypeName(const QString &newMapTypeName);

    const QString &streamLast() const;
    void setStreamLast(const QString &newLastStream);

    bool streamAutoConnect() const;
    void setStreamAutoConnect(bool newStreamAutoConnect);

signals:

    void mapProviderNameChanged();
    void mapTypeNameChanged();

    void streamLastChanged();

    void streamAutoConnectChanged();

private:

    QSettings *m_settings = nullptr;

    // maps
    QString m_mapProviderName;
    QString m_mapTypeName;

    // streaming

    QString m_streamLast;
    bool m_streamAutoConnect;
};

#endif // CONFIGURATION_H
