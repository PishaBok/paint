#pragma once

#include <QPolygon>
#include <paint/shapes/base_shape.hpp>

class Triangle: public BaseShape
{
public:
    Triangle(const QPoint& p1 = {}, const QPoint& p2 = {}, const QPoint& p3 = {});
    virtual ~Triangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;
private:
    QPolygon _polygon;
};