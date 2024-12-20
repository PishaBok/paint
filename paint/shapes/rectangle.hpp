#pragma once

#include <QRect>
#include <paint/shapes/shape.hpp>

class Rectangle: public BaseShape
{
public:
    Rectangle(const QPoint& topLeft, const QPoint& bottomRight);

    void draw(QPainter* painter) override;
    void drawTemporary(QPainter* painter, const QPoint& start, const QPoint& end) override;
    bool contains(const QPoint& point) override;
    void move(const QPoint& delta) override;

    QRect getBoundingRect() const;
private:
    QRect _boundingRect;
};