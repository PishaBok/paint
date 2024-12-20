#pragma once

#include <vector>
#include <QFrame>
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include <paint/shapes/rectangle.hpp>
#include <paint/shapes/triangle.hpp>

class WorkSpace: public QFrame
{
    Q_OBJECT
public:
    WorkSpace(QFrame* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    std::vector<std::unique_ptr<BaseShape>> _shapes;
    QPoint _startPoint;
    QPoint _endPoint;

    bool _isDrawning = false;
    std::unique_ptr<BaseShape> _currentShape;
};