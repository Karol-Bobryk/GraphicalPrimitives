#include "linedrawhub.h"

#include <QDoubleValidator>
#include <QLabel>

LineDrawHub::LineDrawHub(QWidget *parent)
    : QWidget{parent}
    , xPosEdits{new QLineEdit(), new QLineEdit()}
    , yPosEdits{new QLineEdit(), new QLineEdit()}

    , draw_button{new QPushButton("Draw")}
{
    // makes sure edits validate their inputs
    setNumericValidators();

    QVBoxLayout *layout = new QVBoxLayout();

    // two rows of input boxes
    std::array<QHBoxLayout *, 2> edit_layouts = {new QHBoxLayout(), new QHBoxLayout()};

    for (int i = 0; i < 2; ++i) {
        QString x_label = "x" + QString::number(i + 1) + "Pos:";
        QString y_label = "y" + QString::number(i + 1) + "Pos:";

        edit_layouts[i]->addWidget(new QLabel(x_label));

        edit_layouts[i]->addWidget(xPosEdits[i]);
        edit_layouts[i]->addSpacing(5);

        edit_layouts[i]->addWidget(new QLabel(y_label));
        edit_layouts[i]->addWidget(yPosEdits[i]);
    }

    layout->addLayout(edit_layouts[0]);
    layout->addSpacing(5);
    layout->addLayout(edit_layouts[1]);

    layout->addWidget(draw_button);

    this->setLayout(layout);

    connect(draw_button, &QPushButton::clicked, this, &LineDrawHub::handleDraw);
}

std::array<QPointF, 2> LineDrawHub::getPos()
{
    qreal x1, y1;
    qreal x2, y2;

    y1 = yPosEdits[0]->text().toDouble();
    y2 = yPosEdits[1]->text().toDouble();

    x1 = xPosEdits[0]->text().toDouble();
    x2 = xPosEdits[1]->text().toDouble();

    return {QPointF(x1, y1), QPointF(x2, y2)};
}

void LineDrawHub::setNumericValidators()
{
    for (auto edit : xPosEdits)
        edit->setValidator(new QDoubleValidator(0, 500, 2, this));

    for (auto edit : yPosEdits)
        edit->setValidator(new QDoubleValidator(0, 300, 2, this));
}

void LineDrawHub::handleDraw(bool /*unused*/)
{
    std::array<QPointF, 2> points = getPos();

    emit clickedDrawLine(points[0], points[1]);
}