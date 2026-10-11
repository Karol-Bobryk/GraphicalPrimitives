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
    draw_hub->move(0, 100.0);

    draw_hub->addWidget(new LineDrawHub(this));

    // If canvas detects click
    connect(main_view,
            &CustomGraphicsView::canvasClickRegistered,
            this,
            &Window::registerCanvasClick);

    // If picker detects change
    connect(shape_mode_picker, &QComboBox::currentTextChanged, this, &Window::switchDrawingHub);

    // connect(line_draw_hub, &LineDrawHub::clickedDrawLine, this, &Window::drawLine);
}
void Window::drawLine(QPointF a, QPointF b)
{
    main_scene->addLine(QLineF(a, b), currentPen);
}

void Window::drawRectangle(QPointF a, QPointF b)
{
    qInfo() << "drawing rect...";

    qInfo() << "a: " << a.x() << " " << a.y();
    qInfo() << "b: " << b.x() << " " << b.y();
    main_scene->addRect(QRectF(a, b), currentPen);
    main_scene->update();
}

void Window::drawCircle(QPointF a, QPointF b)
{
    main_scene->addEllipse(QRectF(a, b), currentPen);
    main_scene->update();
}

void Window::registerCanvasClick(QPointF point)
{
    clicked_points.push_back(point);
    qInfo() << clicked_points.size();
    for (auto *e : main_scene->items()) {
        // qInfo() <<  ;
    }
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