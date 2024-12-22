#pragma once

#include <QPolygon>
#include <paint/shapes/shape.hpp>

class Triangle: public BaseShape
{
public:
    Triangle(const QPoint& topLeft = {}, const QPoint& bottomRight = {});
    virtual ~Triangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) override;
    void move(const QPoint& delta) override;
    void updateShape(const QPoint& topLeft, const QPoint& bottomRight) override;
private:
    QPoint _thirdPoint;

    double area(const QPoint& a, const QPoint& b, const QPoint& c) const; // Вычисление площади треугольника
};