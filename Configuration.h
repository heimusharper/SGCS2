#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QSettings>
#include <QObject>
#include <QDir>

class Configuration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mapProviderName READ mapProviderName WRITE setMapProviderName NOTIFY mapProviderNameChanged)
    Q_PROPERTY(QString mapTypeName READ mapTypeName WRITE setMapTypeName NOTIFY mapTypeNameChanged)
    Q_PROPERTY(QString connectionUDPHost READ connectionUDPHost WRITE setConnectionUDPHost NOTIFY connectionUDPHostChanged)
    Q_PROPERTY(int connectionUDPPort READ connectionUDPPort WRITE setConnectionUDPPort NOTIFY connectionUDPPortChanged)
    Q_PROPERTY(QString connectionSerialPort READ connectionSerialPort WRITE setConnectionSerialPort NOTIFY connectionSerialPortChanged)
    Q_PROPERTY(QString connectionMethod READ connectionMethod WRITE setConnectionMethod NOTIFY connectionMethodChanged)

    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
public:

    explicit Configuration(QSettings *settings, QObject *parent = nullptr);

    ~Configuration();

    void flush();

    const QString &mapProviderName() const;
    void setMapProviderName(const QString &newMapProviderName);

    const QString &mapTypeName() const;
    void setMapTypeName(const QString &newMapTypeName);

    const QString &connectionUDPHost() const;
    void setConnectionUDPHost(const QString &newConnectionUDPHost);

    int connectionUDPPort() const;
    void setConnectionUDPPort(int newConnectionUDPPort);

    const QString &connectionSerialPort() const;
    void setConnectionSerialPort(const QString &newConnectionSerialPort);

    const QString &connectionMethod() const;
    void setConnectionMethod(const QString &newConnectionMethod);

    Q_INVOKABLE QStringList getLanguages();

    const QString &language() const;
    void setLanguage(const QString &newLanguage);

signals:

    void mapProviderNameChanged();
    void mapTypeNameChanged();

    void connectionUDPHostChanged();

    void connectionUDPPortChanged();

    void connectionSerialPortChanged();

    void connectionMethodChanged();

    void languageChanged(const QString &t);

private:

    QSettings *m_settings = nullptr;

    // maps
    QString m_mapProviderName;
    QString m_mapTypeName;

    QString m_connectionUDPHost;
    int m_connectionUDPPort;
    QString m_connectionSerialPort;
    QString m_connectionMethod;
    QString m_language = "ru_RU";
};

#endif // CONFIGURATION_H
