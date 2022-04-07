#ifndef DATASTREAMER_H
#define DATASTREAMER_H

#include <QObject>

// streamers
#include "PositionDataStream.h"
#include "HomePositionStreamer.h"

class DataStreamer : public QObject
{
    Q_OBJECT
public:
    explicit DataStreamer(QObject *parent = nullptr);
    virtual ~DataStreamer() = default;

public:

    virtual PositionDataStream *getPositionDataStream() = 0;
    virtual HomePositionRequest *createHomePositionRequest() = 0;

signals:

};

#endif // DATASTREAMER_H
