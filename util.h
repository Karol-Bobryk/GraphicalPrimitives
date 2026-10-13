#ifndef UTIL_H
#define UTIL_H
#include <QJsonArray>
#include <QJsonObject>
#include <QPointF>

namespace Util {
QJsonObject jsonObjFromQPointF(const QPointF point);
QJsonArray jsonArrayOfPoints(const std::initializer_list<QPointF> &points);

}; // namespace Util

#endif // UTIL_H
