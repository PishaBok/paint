#include <paint/shapes/triangle.hpp>

Triangle::Triangle(const QPoint& topLeft, const QPoint& bottomRight)
{
    QPoint middlePoint{(topLeft.x() + bottomRight.x()) / 2, (topLeft.y() + bottomRight.y()) / 2};
    int height = std::abs(topLeft.x() - bottomRight.x()) / 2;

    QPoint thirdPoint(middlePoint.x(), middlePoint.y() - height);
    _triangle << topLeft << bottomRight << thirdPoint;
}

void Triangle::draw(QPainter* painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawPolygon(_triangle);
}

void Triangle::drawTemporary(QPainter* painter, const QPoint& start, const QPoint& end)
{
    QPen pen(Qt::black);

    QPoint middlePoint{(start.x() + end.x()) / 2, (start.y() + end.y()) / 2};
    int height = std::abs(start.x() - end.x()) / 2;

    QPoint thirdPoint(middlePoint.x(), middlePoint.y() - height);
    QPolygon triangle;
    triangle << start << end << thirdPoint;

    painter->setPen(pen);
    painter->drawPolygon(triangle);
}

bool Triangle::contains(const QPoint& point)
{
    return _triangle.contains(point);
}

void Triangle::move(const QPoint& delta)
{
    _triangle.translate(delta);
}
