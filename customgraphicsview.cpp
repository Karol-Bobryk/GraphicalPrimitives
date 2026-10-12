#include "customgraphicsview.h"
#include <QGraphicsView>
#include <QMouseEvent>

CustomGraphicsView::CustomGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (draggedItem != nullptr)

    {
        QPointF destination = event->position();
        qreal dx = destination.x() - itemOrigin.x();
        qreal dy = destination.y() - itemOrigin.y();
        draggedItem->moveBy(dx, dy);
        this->scene()->update();
        // TODO validate if is in scene:
        draggedItem = nullptr;
    }
    if (event->button() == Qt::LeftButton)
        emit canvasClickRegistered(event->position());
    else
        QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint clicked_pos = event->position().toPoint();
        QGraphicsItem *item = this->itemAt(mapToScene(clicked_pos).toPoint());

        if (item != nullptr) {
            qInfo() << clicked_pos;
            draggedItem = item;
            itemOrigin = clicked_pos;
        }
    } else
        QGraphicsView::mouseReleaseEvent(event);
}