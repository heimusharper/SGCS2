#ifndef POSITIONDATASTREAM_H
#define POSITIONDATASTREAM_H
#include <QGeoCoordinate>
#include <QVector3D>
#include <QObject>

class PositionDataStream : public QObject
{
    Q_OBJECT
public:
    PositionDataStream(QObject *parent = nullptr)
        : QObject(parent)
    {

    }
    virtual ~PositionDataStream() = default;

signals:

    void onPositionChanged(const QGeoCoordinate &pos);
    /*!
     * \brief onAttitudeChanged
     * \param att {roll pitch yaw} rad
     */
    void onAttitudeChanged(const QVector3D &att);
};

#endif // POSITIONDATASTREAM_H
