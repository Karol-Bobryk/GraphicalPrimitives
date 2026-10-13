#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QJsonArray>
#include <QList>
#include <QPair>
#include <QUrl>

class CustomGraphicsView : public QGraphicsView
{
public:
    Q_OBJECT
public:
    CustomGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void canvasClickRegistered(QPointF point);
    void canvasDeserializedObjects(QList<QPair<QList<QPointF>, QString>> objects);

private:
    QJsonArray serializeCanvas();
    void deserializeCanvas(QByteArray bytes);
    static QJsonObject serializeGraphicsItem(QGraphicsItem *item);
    QPair<QList<QPointF>, QString> deserializeGraphicsItem(QJsonObject obj);

    QGraphicsItem *draggedItem = nullptr;
    QPointF itemOrigin;
public slots:
    void saveToJSONFile(QUrl file_url);
    void loadFromJSONFile(QUrl file_url);
};

#endif // CUSTOMGRAPHICSVIEW_H
