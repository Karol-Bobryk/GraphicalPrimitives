#include "window.h"
#include <QRectF>
#include "linedrawhub.h"

Window::Window(QWidget *parent)
    : QWidget{parent}
    , currentPen{QPen(QColor(144, 137, 16))}
    , main_scene{new QGraphicsScene(QRectF(0, 0, 500.0, 300.0), this)}
    , main_view{new CustomGraphicsView(main_scene, this)} // , draw_hub{new LineDrawHub(this)}
    , draw_hub{new QStackedWidget(this)}
    , shape_mode{ShapeDrawMode::Line}
    , shape_mode_picker{new QComboBox(this)}
{
    shape_mode_picker->addItem("Line");
    shape_mode_picker->addItem("Rectangle");
    shape_mode_picker->addItem("Circle");

    // compose workbar

    this->setFixedSize(600, 500);

    main_view->move(0, 200.0);
    draw_hub->move(0, 50.0);

    auto line_draw_hub = new LineDrawHub(this);
    draw_hub->addWidget(line_draw_hub);

    // If canvas detects click
    connect(main_view,
            &CustomGraphicsView::canvasClickRegistered,
            this,
            &Window::registerCanvasClick);

    // If picker detects change
    connect(shape_mode_picker, &QComboBox::currentTextChanged, this, &Window::switchDrawingHub);

    // i do not care enough to change this name, every shape is made from 2 points anyway
    connect(line_draw_hub, &LineDrawHub::clickedDrawLine, this, &Window::drawFromHub);
}

void Window::drawLine(QPointF a, QPointF b)
{
    main_scene->addLine(QLineF(a, b), currentPen);
}

void Window::drawRectangle(QPointF a, QPointF b)
{
    main_scene->addRect(QRectF(a, b), currentPen);
    main_scene->update();
}

void Window::drawCircle(QPointF center, QPointF radiusPoint)
{
    qreal radius = QLineF(center, radiusPoint).length();

    QPointF topRight(center.x() - radius, center.y() - radius);
    QPointF bottomLeft(center.x() + radius, center.y() + radius);

    main_scene->addEllipse(QRectF(topRight, bottomLeft), currentPen);
    main_scene->update();
}

void Window::drawCurrentShape()
{
    switch (shape_mode) {
    case ShapeDrawMode::Line:
        if (clicked_points.size() == 2) {
            drawLine(clicked_points[0], clicked_points[1]);
            clicked_points.clear();
        }
        break;
    case ShapeDrawMode::Rectangle:
        if (clicked_points.size() == 2) {
            drawRectangle(clicked_points[0], clicked_points[1]);
            clicked_points.clear();
        }
        break;
    case ShapeDrawMode::Circle:
        if (clicked_points.size() == 2) {
            drawCircle(clicked_points[0], clicked_points[1]);
            clicked_points.clear();
        }
        break;
    }
}

void Window::registerCanvasClick(QPointF point)
{
    clicked_points.push_back(point);
    drawCurrentShape();
}

void Window::drawFromHub(QPointF a, QPointF b)
{
    clicked_points.clear();
    clicked_points.push_back(a);
    clicked_points.push_back(b);
    drawCurrentShape();
}

void Window::switchDrawingHub(const QString &text)
{
    if (text == "Line")
        shape_mode = ShapeDrawMode::Line;
    if (text == "Rectangle")
        shape_mode = ShapeDrawMode::Rectangle;
    if (text == "Circle")
        shape_mode = ShapeDrawMode::Circle;

    clicked_points.clear();
}