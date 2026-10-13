#include "window.h"
#include <QLine>
#include <QRectF>
#include "linedrawhub.h"

Window::Window(QWidget *parent)
    : QWidget{parent}
    , current_pen{QPen(QColor(135, 221, 246))}
    , main_scene{new QGraphicsScene(QRectF(0, 0, 500.0, 300.0), this)}
    , main_view{new CustomGraphicsView(main_scene, this)}
    , draw_hub{new QStackedWidget(this)}
    , shape_mode{ShapeDrawMode::Line}
    , shape_mode_picker{new QComboBox(this)}
    , serialization_hub(new SerializationHub(this))
{
    current_pen.setWidth(5);

    shape_mode_picker->addItem("Line");
    shape_mode_picker->addItem("Rectangle");
    shape_mode_picker->addItem("Circle");
    shape_mode_picker->addItem("Drag");

    // compose workbar
    this->setFixedSize(600, 500);

    shape_mode_picker->move(10, 10);
    main_view->move(0, 200.0);
    draw_hub->move(0, 50.0);

    serialization_hub->move(200.0, 0);

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

    // If save clicked
    connect(serialization_hub,
            &SerializationHub::saveLayoutRequested,
            main_view,
            &CustomGraphicsView::saveToJSONFile);

    connect(serialization_hub,
            &SerializationHub::loadLayoutRequested,
            main_view,
            &CustomGraphicsView::loadFromJSONFile);

    connect(main_view,
            &CustomGraphicsView::canvasDeserializedObjects,
            this,
            &Window::drawFromSaveFile);
}

void Window::drawLine(QPointF a, QPointF b)
{
    main_scene->addLine(QLineF(a, b), current_pen);
}

void Window::drawRectangle(QPointF a, QPointF b)
{
    main_scene->addRect(QRectF(a, b), current_pen);
    main_scene->update();
}

void Window::drawCircle(QPointF center, QPointF radiusPoint)
{
    qreal radius = QLineF(center, radiusPoint).length();

    QPointF topRight(center.x() - radius, center.y() - radius);
    QPointF bottomLeft(center.x() + radius, center.y() + radius);

    main_scene->addEllipse(QRectF(topRight, bottomLeft), current_pen);
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
    case ShapeDrawMode::Off:
        return;
    }
}

void Window::registerCanvasClick(QPointF point)
{
    if (shape_mode == ShapeDrawMode::Off)
        return;

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

void Window::drawFromSaveFile(QList<QPair<QList<QPointF>, QString>> objects)
{
    clicked_points.clear();
    ShapeDrawMode current_mode = shape_mode;
    for (const auto &pair : objects) {
        QPointF p1 = pair.first[0];
        QPointF p2 = pair.first[1];
        QString shape = pair.second;

        switchDrawingHub(shape);

        clicked_points.push_back(p1);
        clicked_points.push_back(p2);

        drawCurrentShape();
    }

    shape_mode = current_mode;
}

void Window::switchDrawingHub(QString text)
{
    qInfo() << text;
    if (text == "Line")
        shape_mode = ShapeDrawMode::Line;
    else if (text == "Rectangle")
        shape_mode = ShapeDrawMode::Rectangle;
    else if (text == "Circle")
        shape_mode = ShapeDrawMode::Circle;
    else
        shape_mode = ShapeDrawMode::Off;

    clicked_points.clear();
}
