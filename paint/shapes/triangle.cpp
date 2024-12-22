#include <paint/shapes/triangle.hpp>

Triangle::Triangle(const QPoint& topLeft, const QPoint& bottomRight)
    : BaseShape(topLeft, bottomRight)
{}

void Triangle::draw(QPainter* painter)
{
    QPolygon triangle;
    triangle << _topLeft << _bottomRight << _thirdPoint;

    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawPolygon(triangle);
}

bool Triangle::contains(const QPoint& point)
{
    double A = area(_topLeft, _bottomRight, _thirdPoint);
    double A1 = area(point, _bottomRight, _thirdPoint);
    double A2 = area(_topLeft, point, _thirdPoint);
    double A3 = area(_topLeft, _bottomRight, point);

    return std::abs(A - (A1 + A2 + A3)) < 1e-6; // Учитываем погрешность
}

void Triangle::move(const QPoint& delta)
{
   // _triangle.translate(delta);
}

void Triangle::updateShape(const QPoint& topLeft, const QPoint& bottomRight)
{
    BaseShape::updateShape(topLeft, bottomRight); // Вызываем базовую реализацию

    // Находим третью точку
    QPoint middlePoint{(_topLeft.x() + _bottomRight.x()) / 2, (_topLeft.y() + _bottomRight.y()) / 2};
    int height = std::abs(_topLeft.x() - _bottomRight.x()) / 2;
    _thirdPoint = QPoint{middlePoint.x(), middlePoint.x() / 2};
}


double Triangle::area(const QPoint& a, const QPoint& b, const QPoint& c) const
{
    return std::abs((a.x() * (b.y() - c.y()) +
                         b.x() * (c.y() - a.y()) +
                         c.x() * (a.y() - b.y())) / 2.0);
}
