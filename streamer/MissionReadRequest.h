#ifndef MISSIONREADREQUEST_H
#define MISSIONREADREQUEST_H

#include <QObject>

class MissionReadRequest : public QObject
{
    Q_OBJECT
public:
    explicit MissionReadRequest(QObject *parent = nullptr)
        : QObject(parent)
    {
    }
    enum Errors {
        ERR_FAILED_GET_COUNT,
        ERR_FAILED_GET_INDEX
    };
    enum PointType {
        SIMPLE_POINT
    };

signals:

    // void onError(MissionReadRequest::Errors err);
    void onItem(uint16_t seq, MissionReadRequest::PointType type, float p1, float p2, float p3, float p4, double x, double y, double z);
    void progress(float stat);
};

#endif // MISSIONREADREQUEST_H
