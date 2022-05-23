#ifndef ARMREQUEST_H
#define ARMREQUEST_H

#include <QObject>

class ARMRequest : public QObject
{
    Q_OBJECT
public:
    enum Mode {
        ARM,
        DISARM,
        TAKEOFF,
        MISSION_START
    };

    explicit ARMRequest(Mode mode, QObject *parent = nullptr)
        : QObject(parent)
        , m_mode(mode)
    {
    }

protected:

    Mode m_mode;

signals:
};

#endif // ARMREQUEST_H
