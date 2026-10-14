#include "util.h"

QJsonObject Util::jsonObjFromQPointF(const QPointF point)
{
    QJsonObject obj;
    obj.insert("x", point.x());
    obj.insert("y", point.y());
    return obj;
}

QJsonArray Util::jsonArrayOfPoints(const std::initializer_list<QPointF> &points)
{
    QJsonArray arr;

    for (auto e : std::as_const(points)) {
        arr.append(Util::jsonObjFromQPointF(e));
    }
    return arr;
}

QPointF Util::QPointFFromJsonObj(const QJsonObject &obj)
{
    QPointF point;

    if (obj.isEmpty()) {
        qInfo() << "point object cannot be empty";
        return point;
    }

    QJsonValue x_pos = obj.value("x");
    QJsonValue y_pos = obj.value("y");

    if (!x_pos.isDouble() || !y_pos.isDouble()) {
        qInfo() << "point coordinates have to be of a number (double) type";
        return point;
    }

    point.setX(x_pos.toDouble());
    point.setY(y_pos.toDouble());

    return point;
}

QList<QPointF> Util::pointsFromJsonArray(const QJsonArray &arr)
{
    QList<QPointF> list;

    for (auto e : arr) {
        if (e.isObject())
            list.append(Util::QPointFFromJsonObj(e.toObject()));
    }

    return list;
}

QList<QPointF> Util::getPointsFromGenericItem(QGraphicsItem *item)
{
    QList<QPointF> list;
    switch (item->type()) {
    case QGraphicsLineItem::Type: {
        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);

        return {line->line().p1(), line->line().p2()};
    }
    case QGraphicsRectItem::Type: // rectangle // TODO
    {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem *>(item);

        QPointF p1 = rect->rect().topLeft();
        QPointF p2 = rect->rect().topRight();

        QPointF p3 = rect->rect().bottomLeft();
        QPointF p4 = rect->rect().bottomRight();

        return {p1, p2, p3, p4};
    }
    case QGraphicsEllipseItem::Type: // elipsis
    {
        QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        QPointF p1 = ellipse->rect().center();
        QPointF p2 = ellipse->rect().bottomLeft();
        // circles are constructed via a nonstandard method so I had to convert it to be a point on the arc
        QPointF leftUp = ellipse->rect().topLeft();
        p2.setY(leftUp.y() + (p2.y() - leftUp.y()) / 2);

        return {p1, leftUp};
        break;
    }
    default: // unknown or unsupported
        qInfo() << "Unknown or unsupported shape type detected while saving";
    }

    return {};
}