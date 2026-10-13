#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QJsonArray>
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

private:
    QJsonArray serializeCanvas();
    void deserializeCanvas();
    static QJsonObject serializeGraphicsItem(QGraphicsItem *item);

    QGraphicsItem *draggedItem = nullptr;
    QPointF itemOrigin;
public slots:
    void saveToJSONFile(QUrl file_url);
    void loadFromJSONFile(QUrl file_url);
};

#endif // CUSTOMGRAPHICSVIEW_H
