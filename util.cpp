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