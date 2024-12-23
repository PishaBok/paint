#include <paint/shapes/triangle.hpp>

Triangle::Triangle(const QPoint& p1, const QPoint& p2, const QPoint& p3)
    : _polygon{QPolygon({p1, p2, p3})}
{}

void Triangle::draw(QPainter* painter)
{
    painter->drawPolygon(_polygon);
}

bool Triangle::contains(const QPoint& point) const
{
    return _polygon.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::resize(const QRect& newBounds)
{
    QPoint center = newBounds.center();
    int width = newBounds.width();
    int height = newBounds.height();
    _polygon[0] = QPoint(center.x(), center.y() - height / 2);
    _polygon[1] = QPoint(center.x() - width / 2, center.y() + height / 2);
    _polygon[2] = QPoint(center.x() + width / 2, center.y() + height / 2);
}

void Triangle::move(const QPoint& delta)
{
    _polygon.translate(delta);
}

QPoint Triangle::center() const
{
    int x = (_polygon[0].x() + _polygon[1].x() + _polygon[2].x()) / 3;
    int y = (_polygon[0].y() + _polygon[1].y() + _polygon[2].y()) / 3;
    return QPoint(x, y);
}

QRect Triangle::boundingRect() const
{
    return _polygon.boundingRect();
}

