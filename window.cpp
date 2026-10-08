#include "window.h"
#include <QRectF>

Window::Window(QWidget *parent)
    : QWidget{parent}
    , main_scene{new QGraphicsScene(QRectF(0, 0, 500.0, 300.0), this)}
    , main_view{new QGraphicsView(main_scene, this)}
    , draw_hub{new LineDrawHub(this)}
{
    this->setFixedSize(500, 500);

    main_view->move(0, 200.0);

    connect(draw_hub, &LineDrawHub::clickedDrawLine, this, &Window::drawLine);
}
void Window::drawLine(QPointF a, QPointF b)
{
    main_scene->addLine(QLineF(a, b), QPen(QColor(144, 137, 16)));
}