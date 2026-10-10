#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
public:
    Q_OBJECT
public:
    CustomGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void canvasClickRegistered(QPointF point);
};

#endif // CUSTOMGRAPHICSVIEW_H
