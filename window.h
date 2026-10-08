#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "linedrawhub.h"

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
private:
    QGraphicsScene *main_scene;
    QGraphicsView *main_view;
    LineDrawHub *draw_hub;
signals:

private slots:
    void drawLine(QPointF a, QPointF b);
};

#endif // WINDOW_H