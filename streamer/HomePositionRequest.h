#ifndef HOMEPOSITIONSTREAMER_H
#define HOMEPOSITIONSTREAMER_H
#include <QGeoCoordinate>
#include <QObject>

class HomePositionRequest : public QObject {
    Q_OBJECT
public:
    HomePositionRequest(QObject *parent)
        : QObject(parent)
    {
    }

signals:

    void onHomePositionChanged(const QGeoCoordinate &pos);
};

#endif // HOMEPOSITIONSTREAMER_H
