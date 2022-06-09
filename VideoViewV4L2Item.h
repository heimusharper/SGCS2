#ifndef VIDEOVIEWV4L2ITEM_H
#define VIDEOVIEWV4L2ITEM_H

#include <QQuickItem>
#include <QSGGeometryNode>
#include <QQuickWindow>
#include <QImage>
#include <QSGSimpleTextureNode>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

class VideoFrameGrabber : public QAbstractVideoSurface {
    Q_OBJECT
public:
    VideoFrameGrabber(QObject *parent = nullptr) : QAbstractVideoSurface(parent)
    {

    }
    virtual ~VideoFrameGrabber() = default;
    virtual bool isFormatSupported(const QVideoSurfaceFormat &format) const {
        return QAbstractVideoSurface::isFormatSupported(format);
    }
    virtual QVideoSurfaceFormat nearestFormat(const QVideoSurfaceFormat &format) const {
        return QAbstractVideoSurface::nearestFormat(format);
    }
    virtual bool present(const QVideoFrame &frame) {
        m_lastFrame = frame;
        m_frameDirty = true;
        return true;
    }
    virtual bool start(const QVideoSurfaceFormat &format) {
        return QAbstractVideoSurface::start(format);
        qDebug() << "start";
    }
    virtual void stop() {
        qDebug() << "stop";
    }
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const{
        if (type == QAbstractVideoBuffer::NoHandle) {
            return QList<QVideoFrame::PixelFormat>()
                   << QVideoFrame::Format_RGB24;
        } else {
            return QList<QVideoFrame::PixelFormat>();
        }
    }

    QImage getImage() {
        if (m_frameDirty) {
            m_frameDirty = false;
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(m_lastFrame.pixelFormat());
            m_lastFrame.map(QAbstractVideoBuffer::ReadOnly);
            QImage img(m_lastFrame.bits(),
                       m_lastFrame.width(),
                       m_lastFrame.height(),
                       imageFormat);
            m_lastFrame.unmap();
            return img;
        }
        return QImage();
    }
    bool frameDirty () const {
        return m_frameDirty;
    }

private:
    bool m_frameDirty = false;
    QVideoFrame m_lastFrame;
};

class VideoViewV4L2Item : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit VideoViewV4L2Item(QQuickItem *parent = nullptr);

    Q_INVOKABLE void run(const QString &address);

    virtual ~VideoViewV4L2Item();

private:
    virtual QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData) override;

private:
    void releaseResources() override;

    QTimer *m_timer = nullptr;

    QMediaPlayer *m_player = nullptr;
    VideoFrameGrabber *m_frames = nullptr;
};

#endif // VIDEOVIEWV4L2ITEM_H
