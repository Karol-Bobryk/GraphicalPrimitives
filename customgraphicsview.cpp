#include "customgraphicsview.h"
#include <QFile>
#include <QGraphicsView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>
#include "util.h"

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

void CustomGraphicsView::saveToJSONFile(QUrl file_url)
{
    QFile save_file(file_url.path());
    if (!save_file.open(QIODeviceBase::WriteOnly)) {
        qInfo() << "failed to open file for saving";
        return;
    }

    QJsonDocument document;

    document.setArray(serializeCanvas());

    QByteArray bytes = document.toJson();
    if (save_file.write(bytes) == -1)
        qInfo() << "failed to save layout";
    save_file.close();
}

void CustomGraphicsView::loadFromJSONFile(QUrl file_url) {}

QJsonArray CustomGraphicsView::serializeCanvas()
{
    QList<QGraphicsItem *> drawn_items = scene()->items();

    QJsonArray arr;

    for (auto e : std::as_const(drawn_items)) {
        arr.append(serializeGraphicsItem(e));
    }

    return arr;
}

void CustomGraphicsView::deserializeCanvas() {}

QJsonObject CustomGraphicsView::serializeGraphicsItem(QGraphicsItem *item)
{
    QJsonObject obj;
    if (item == nullptr) {
        qInfo() << "graphics item cannot be null";
        return QJsonObject();
    }

    switch (item->type()) {
    case QGraphicsLineItem::Type: {
        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);

        QPointF p1 = line->line().p1();
        QPointF p2 = line->line().p2();

        QJsonArray points = Util::jsonArrayOfPoints({p1, p2});

        obj.insert("type", "LINE");
        obj.insert("points", points);

        break;
    }
    case QGraphicsRectItem::Type: // rectangle // TODO
    {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem *>(item);

        QPointF p1 = rect->rect().topLeft();
        QPointF p2 = rect->rect().bottomRight();

        QJsonArray points = Util::jsonArrayOfPoints({p1, p2});

        obj.insert("type", "RECTANGLE");
        obj.insert("points", points);

        break;
    }
    case QGraphicsEllipseItem::Type: // elipsis
    {
        QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        QPointF p1 = ellipse->rect().topLeft();
        QPointF p2 = ellipse->rect().bottomRight();

        QJsonArray points = Util::jsonArrayOfPoints({p1, p2});

        obj.insert("type", "ELLIPSE");
        obj.insert("points", points);

        break;
    }
    default: // unknown or unsupported
        qInfo() << "Unknown or unsupported shape type detected while saving";
    }
    return obj;
}