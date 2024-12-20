#pragma once

#include <QRect>
#include <QPolygon>
#include <paint/shapes/shape.hpp>

class Triangle: public BaseShape
{
public:
    Triangle(const QPoint& topLeft, const QPoint& bottomRight);

    void draw(QPainter* painter) override;
    void drawTemporary(QPainter* painter, const QPoint& start, const QPoint& end) override;
    bool contains(const QPoint& point) override;
    void move(const QPoint& delta) override;
private:
    QPolygon _triangle;
};