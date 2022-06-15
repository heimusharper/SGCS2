#ifndef MANUALCONTROLREQUEST_H
#define MANUALCONTROLREQUEST_H
#include <QGeoCoordinate>
#include <QObject>

class ManualControlRequest : public QObject {
    Q_OBJECT
public:
    ManualControlRequest(QObject *parent)
        : QObject(parent)
    {
    }
    virtual void doLand() = 0;
    virtual void doRTL() = 0;
    virtual void doMission() = 0;

    virtual void goTo(const QGeoCoordinate &pos) = 0;
signals:

};
#endif // MANUALCONTROLREQUEST_H
