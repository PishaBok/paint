#pragma once

#include <QPainter>
#include <QPoint>
#include <QSize>


class BaseShape
{
public:
    BaseShape(const QPoint& topLeft = {}, const QPoint& bottomRight = {}) 
        : _topLeft{topLeft}, _bottomRight{bottomRight}
    {}
    virtual ~BaseShape() = default;

    virtual void draw(QPainter* painter) = 0;
    virtual bool contains(const QPoint& point) = 0;
    virtual void move(const QPoint& delta) = 0;
    virtual void updateShape(const QPoint& topLeft, const QPoint& bottomRight)
    {
        _topLeft = topLeft;
        _bottomRight = bottomRight;
    }
    QPoint center() const
    {
        QSize size = QSize{_bottomRight.x() - _topLeft.x(), _bottomRight.y() - _topLeft.y()};
        return _topLeft + QPoint(size.width() / 2, size.height() / 2); // Получаем центр фигуры
    }

protected:
    QPoint _topLeft;
    QPoint _bottomRight;
} ;
