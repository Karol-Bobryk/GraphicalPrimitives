#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "customgraphicsview.h"
#include "linedrawhub.h"
#include <vector>

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
private:
    QGraphicsScene *main_scene;
    CustomGraphicsView *main_view;
    LineDrawHub *draw_hub;

signals:

private slots:
    void drawLine(QPointF a, QPointF b);
    void registerCanvasClick(QPointF point);

private:
    enum class ShapeDrawMode { Line, Triangle, Rectangle, Circle };
    std::vector<QPointF> clickedPoints;
    ShapeDrawMode shapeMode;
};

#endif // WINDOW_H