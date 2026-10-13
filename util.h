#ifndef UTIL_H
#define UTIL_H
#include <QJsonArray>
#include <QJsonObject>
#include <QPointF>

namespace Util {
QJsonObject jsonObjFromQPointF(const QPointF point);
QJsonArray jsonArrayOfPoints(const std::initializer_list<QPointF> &points);

QPointF QPointFFromJsonObj(const QJsonObject &obj);
QList<QPointF> pointsFromJsonArray(const QJsonArray &arr);
}; // namespace Util

#endif // UTIL_H
