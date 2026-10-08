#ifndef LINEDRAWHUB_H
#define LINEDRAWHUB_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class LineDrawHub : public QWidget
{
    Q_OBJECT
public:
    explicit LineDrawHub(QWidget *parent = nullptr);

private:
    std::array<QLineEdit *, 2> yPosEdits;
    std::array<QLineEdit *, 2> xPosEdits;

    QPushButton *draw_button;

    std::array<QPointF, 2> getPos();
    void setNumericValidators();
signals:
    void clickedDrawLine(QPointF a, QPointF b);
private slots:
    void handleDraw(bool checked);
};

#endif // LINEDRAWHUB_H
