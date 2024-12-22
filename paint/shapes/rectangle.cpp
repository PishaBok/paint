#include <paint/shapes/rectangle.hpp>

Rectangle::Rectangle(const QPoint& topLeft, const QPoint& bottomRight)
    : BaseShape(topLeft, bottomRight)
{}

void Rectangle::draw(QPainter* painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(_topLeft, _bottomRight));
}

bool Rectangle::contains(const QPoint& point)
{
    QRect rect = QRect(_topLeft, _bottomRight);
    return rect.contains(point);
}

void Rectangle::move(const QPoint& delta)
{
    //_boundingRect.translate(delta);
}
