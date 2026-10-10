#include "window.h"
#include <QRectF>

Window::Window(QWidget *parent)
    : QWidget{parent}
    , main_scene{new QGraphicsScene(QRectF(0, 0, 500.0, 300.0), this)}
    , main_view{new CustomGraphicsView(main_scene, this)}
    , draw_hub{new LineDrawHub(this)}
    , shapeMode{ShapeDrawMode::Line}
{
    this->setFixedSize(500, 500);

    main_view->move(0, 200.0);

    connect(main_view,
            &CustomGraphicsView::canvasClickRegistered,
            this,
            &Window::registerCanvasClick);

    connect(draw_hub, &LineDrawHub::clickedDrawLine, this, &Window::drawLine);
}
void Window::drawLine(QPointF a, QPointF b)
{
    main_scene->addLine(QLineF(a, b), QPen(QColor(144, 137, 16)));
}

void Window::registerCanvasClick(QPointF point)
{
    clickedPoints.push_back(point);
    switch (shapeMode) {
    case ShapeDrawMode::Line:
        if (clickedPoints.size() == 2) {
            drawLine(clickedPoints[0], clickedPoints[1]);
            clickedPoints.clear();
        }
        break;
    case ShapeDrawMode::Triangle:
        if (clickedPoints.size() == 3)
            // TODO: add shapes
            break;
    case ShapeDrawMode::Rectangle:
        if (clickedPoints.size() == 4)
            // TODO: add shapes
            break;
    case ShapeDrawMode::Circle:
        if (clickedPoints.size() == 2)
            // TODO: add shapes
            break;
    }
}