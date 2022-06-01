#ifndef VIDEOVIEWV4L2ITEM_H
#define VIDEOVIEWV4L2ITEM_H

#include <QQuickItem>
#include <QSGGeometryNode>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QTimer>


class VideoViewV4L2Item : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit VideoViewV4L2Item(QQuickItem *parent = nullptr);

    virtual ~VideoViewV4L2Item();

private:
    virtual QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData) override;

private:
    void releaseResources() override;

    QTimer *m_timer = nullptr;
};

#endif // VIDEOVIEWV4L2ITEM_H
