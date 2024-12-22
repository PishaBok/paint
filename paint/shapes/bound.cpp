#include <paint/shapes/bound.hpp>

Bound::Bound(BaseShape* start, BaseShape* end)
    : BaseShape(QPoint{}, QPoint{}), _start{start}, _end{end}
{}

void Bound::draw(QPainter* painter)
{
    if (_start && _end)
    {
        painter->setPen(Qt::black);
        painter->drawLine(_start->center(), _end->center());
    }
}


bool Bound::contains(const QPoint& point)
{
    return false;
}

void Bound::move(const QPoint& delta)
{

}

bool Bound::isUsedByShape(BaseShape* shape) const
{
    return (shape == _start || shape == _end);
}

