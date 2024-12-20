#pragma once

#include <QPainter>
#include <QRect>
#include <QPoint>


class BaseShape
{
public:
    virtual ~BaseShape() {}

    virtual void draw(QPainter* painter) = 0;
    virtual void drawTemporary(QPainter* painter, const QPoint& start, const QPoint& end) = 0;
    virtual bool contains(const QPoint& point) = 0;
    virtual void move(const QPoint& delta) = 0;
} ;
