#ifndef HOMEPOSITIONSTREAMER_H
#define HOMEPOSITIONSTREAMER_H
#include <QGeoCoordinate>
#include <QObject>

class HomePositionRequest : public QObject {
    Q_OBJECT
public:
    HomePositionRequest() {

    }

signals:

    void onHomePositionChanged(const QGeoCoordinate &pos);
};

#endif // HOMEPOSITIONSTREAMER_H
