#pragma once

#include <QDebug>
#include <paint/shapes/shape.hpp>

class Bound: public BaseShape
{
public:
    Bound(BaseShape* start, BaseShape* end);
    virtual ~Bound() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) override;
    void move(const QPoint& delta) override;

    bool isUsedByShape(BaseShape* shape) const;
private:
    BaseShape* _start;
    BaseShape* _end;
};