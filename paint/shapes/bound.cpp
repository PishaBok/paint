#include <paint/shapes/bound.hpp>

Bound::Bound(BaseShape* start, BaseShape* end)
    : _start{start}, _end{end}
{}

void Bound::draw(QPainter* painter)
{
    if (_start && _end) {painter->drawLine(_start->center(), _end->center());}
}

bool Bound::isUsedByShape(BaseShape* shape) const
{
    return (shape == _start || shape == _end);
}

