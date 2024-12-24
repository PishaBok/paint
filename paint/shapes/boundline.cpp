#include <paint/shapes/boundline.hpp>

BoundLine::BoundLine(BaseShape* start, BaseShape* end)
    : BaseShape(ShapeType::bound), _start{start}, _end{end}
{}

void BoundLine::draw(QPainter* painter)
{
    if (_start && _end) {painter->drawLine(_start->center(), _end->center());}
}

bool BoundLine::isUsedByShape(BaseShape* shape) const
{
    return (shape == _start || shape == _end);
}

QJsonObject BoundLine::serialize() const
{
    QJsonObject rectObj;
    rectObj["id"] = _id;
    rectObj["type"] = static_cast<int>(_type);
    
    // Сохраняем в данные id связанных фигур
    QJsonObject dataObj;
    dataObj["start"] = _start->id();
    dataObj["end"] = _end->id();

    rectObj["data"] = dataObj;

    return rectObj;
}

void BoundLine::deserialize(const QJsonObject& jsonObj)
{
    _id = jsonObj["id"].toString();
    _type = static_cast<ShapeType>(jsonObj["type"].toInt());
}

