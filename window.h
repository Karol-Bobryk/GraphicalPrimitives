#ifndef WINDOW_H
#define WINDOW_H

#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "customgraphicsview.h"
#include <vector>

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
private:
    QVBoxLayout *workbar;
    QGraphicsScene *main_scene;
    CustomGraphicsView *main_view;
    QComboBox *shape_mode_picker;
    QStackedWidget *draw_hub;
    QPen currentPen;
signals:

private slots:
    void drawLine(QPointF a, QPointF b);
    void drawRectangle(QPointF a, QPointF b);
    void drawCircle(QPointF a, QPointF b);
    void drawFromHub(QPointF a, QPointF b);
    void drawCurrentShape();
    void registerCanvasClick(QPointF point);
    void switchDrawingHub(const QString &text);

private:
    enum class ShapeDrawMode { Line, Rectangle, Circle };
    std::vector<QPointF> clicked_points;
    ShapeDrawMode shape_mode;
};

#endif // WINDOW_H