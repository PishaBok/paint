#include <paint/shapes/rectangle.hpp>

Rectangle::Rectangle(const QPoint& topLeft, const QPoint& bottomRight)
    : _boundingRect(QRect(topLeft, bottomRight))
{}

void Rectangle::draw(QPainter* painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(_boundingRect);
}

void Rectangle::drawTemporary(QPainter* painter, const QPoint& start, const QPoint& end)
{
    QPen pen(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawRect(QRect(start, end));
}

bool Rectangle::contains(const QPoint& point)
{
    return _boundingRect.contains(point);
}

void Rectangle::move(const QPoint& delta)
{
    _boundingRect.translate(delta);
}

QRect Rectangle::getBoundingRect() const
{
    return _boundingRect;
}