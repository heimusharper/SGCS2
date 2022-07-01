#ifndef PHOTOMODEREQUEST_H
#define PHOTOMODEREQUEST_H

#include <QObject>

class PhotoModeRequest : public QObject
{
    Q_OBJECT
public:
    explicit PhotoModeRequest(float time, float dst, QObject *parent = nullptr)
        : QObject(parent),
          m_time(time),
          m_distance(dst)
    {

    }
    virtual ~PhotoModeRequest() = default;


protected:

    float m_time;
    float m_distance;


signals:
    void onSet(float time, float dts);

};

#endif // PHOTOMODEREQUEST_H
