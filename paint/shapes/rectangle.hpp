#pragma once

#include <QRect>
#include <paint/shapes/shape.hpp>

class Rectangle: public BaseShape
{
public:
    Rectangle(const QPoint& topLeft = {}, const QPoint& bottomRight = {});
    virtual ~Rectangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) override;
    void move(const QPoint& delta) override;
};