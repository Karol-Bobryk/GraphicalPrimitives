#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>

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
    QGraphicsItem *draggedItem = nullptr;
    QPointF itemOrigin;
};

#endif // CUSTOMGRAPHICSVIEW_H
