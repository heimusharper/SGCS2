#ifndef MISSIONWRITEREQUEST_H
#define MISSIONWRITEREQUEST_H

#include <QObject>

class MissionWriteRequest : public QObject
{
    Q_OBJECT
public:
    explicit MissionWriteRequest(QObject *parent = nullptr);

signals:
    void progress(float stat);
};

#endif // MISSIONWRITEREQUEST_H
