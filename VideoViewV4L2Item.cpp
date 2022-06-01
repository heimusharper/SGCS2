#include "VideoViewV4L2Item.h"

VideoViewV4L2Item::VideoViewV4L2Item(QQuickItem *parent)
    : QQuickItem{parent}
{
    setFlag(ItemHasContents);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        // update video
        update();
    });
    m_timer->start(100);
}

VideoViewV4L2Item::~VideoViewV4L2Item()
{

}

QSGNode *VideoViewV4L2Item::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleTextureNode();
        QSGTexture *texture = window()->createTextureFromImage(QImage(":/icons/light/128x128/satelites.png"));
        node->setTexture(texture);
    }
    qDebug() << "Update video";
    node->setRect(boundingRect());
    return node;
}

void VideoViewV4L2Item::releaseResources()
{

}
