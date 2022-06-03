#include "VideoViewV4L2Item.h"

VideoViewV4L2Item::VideoViewV4L2Item(QQuickItem *parent)
    : QQuickItem{parent}
{
    m_frames = new VideoFrameGrabber(this);
    m_player = new QMediaPlayer(this);
    m_player->setMuted(true);
    m_player->setVideoOutput(m_frames);
    m_player->setMedia(QMediaContent(QUrl("v4l2:///dev/video0")));

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        // update video
        update();
    });
    m_timer->start(1000);
    setFlag(ItemHasContents);
    m_player->play();
}

VideoViewV4L2Item::~VideoViewV4L2Item()
{

}

QSGNode *VideoViewV4L2Item::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node || m_frames->frameDirty()) {
        if(!node)
            node = new QSGSimpleTextureNode();
        QImage image = m_frames->getImage();
        if (!image.isNull()) {
            qDebug() << "on frame" << image.width() << image.height() << image.bytesPerLine();
            QSGTexture *texture = window()->createTextureFromImage(image, QQuickWindow::TextureIsOpaque);
            qDebug() << texture->textureSize() << texture->textureId();
            // node->setSourceRect(0, 0, image.width(), image.height());
            node->setOwnsTexture(true);
            node->setRect(boundingRect());
            node->markDirty(QSGNode::DirtyForceUpdate);
            node->setTexture(texture);
        } else if (!node->texture()){
            image = QImage(":/icons/light/128x128/satelites.png");
            QSGTexture *texture = window()->createTextureFromImage(image);
            node->setOwnsTexture(true);
            node->setRect(boundingRect());
            node->markDirty(QSGNode::DirtyForceUpdate);
            node->setTexture(texture);
        }
    }
    //qDebug() << "Update video";
    node->setRect(boundingRect());

    return node;
}

void VideoViewV4L2Item::releaseResources()
{

}
