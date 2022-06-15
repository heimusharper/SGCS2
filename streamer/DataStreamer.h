#ifndef DATASTREAMER_H
#define DATASTREAMER_H

#include <QObject>

// streamers
#include "MainDataStream.h"
#include "PositionDataStream.h"
#include "HomePositionRequest.h"
#include "ManualControlRequest.h"
#include "SensorsDataStream.h"
#include "ARMRequest.h"

class DataStreamer : public QObject
{
    Q_OBJECT
public:
    explicit DataStreamer(QObject *parent = nullptr);
    virtual ~DataStreamer() = default;

public slots:

    virtual void onDataReceived(const QByteArray &data) = 0;

public:

    virtual PositionDataStream *getPositionDataStream() = 0;
    virtual SensorsDataStream *getSensorsStream() = 0;
    virtual MainDataStream *getMainStream() = 0;

    virtual HomePositionRequest *createHomePositionRequest() = 0;
    virtual ARMRequest *createARMRequest(ARMRequest::Mode mode) = 0;
    virtual ManualControlRequest *createManualControlRequest() = 0;

signals:

    void writeData(const QByteArray &data);
};

#endif // DATASTREAMER_H
