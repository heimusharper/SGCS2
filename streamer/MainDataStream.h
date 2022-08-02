#ifndef MAINDATASTREAM_H
#define MAINDATASTREAM_H

#include <QObject>

class MainDataStream : public QObject
{
    Q_OBJECT
public:
    enum ControlMode {
        UNSUPORTED,
        WAIT,
        ARMED,
        TAKEOFF,
        GUIDED,
        GUIDED_RC,
        AUTO,
        RTL,
        LAND,
        FOLOW
    };
    enum UavType {
        COPTER,
        PLANE,
        VTOL,
        UNDEFINED
    };

    MainDataStream(QObject *parent = nullptr)
        : QObject(parent)
    {

    }
    virtual ~MainDataStream() = default;

signals:

    void onControlModeChanged(int i);
    void onUavTypeChanged(int i);
};


#endif // MAINDATASTREAM_H
