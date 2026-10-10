#include "customgraphicsview.h"
#include <QMouseEvent>

CustomGraphicsView::CustomGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit canvasClickRegistered(event->position());
    else
        QGraphicsView::mouseReleaseEvent(event);
}