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