#include <paint/shapes/rectangle.hpp>

Rectangle::Rectangle(const QRect& rect)
    : BaseShape(ShapeType::rectangle), _rect{rect}
{}

void Rectangle::draw(QPainter* painter)
{
    painter->drawRect(_rect);
}

bool Rectangle::contains(const QPoint& point) const
{
    return _rect.contains(point);
}

void Rectangle::resize(const QRect& newBounds)
{
    _rect = newBounds;
}

void Rectangle::move(const QPoint& delta)
{
    _rect.translate(delta);
}

QPoint Rectangle::center() const
{
    return _rect.center();
}

QRect Rectangle::boundingRect() const
{
    return _rect;
}

QJsonObject Rectangle::serialize() const
{
    QJsonObject rectObj;
    rectObj["id"] = _id;
    rectObj["type"] = static_cast<int>(_type);
    
    QJsonObject dataObj;
    dataObj["rectangle"] = rectToJson(_rect);

    rectObj["data"] = dataObj;

    return rectObj;
}

void Rectangle::deserialize(const QJsonObject& jsonObj)
{
    _id = jsonObj["id"].toString();
    _type = static_cast<ShapeType>(jsonObj["type"].toInt());

    QJsonObject dataObj = jsonObj["data"].toObject();
    _rect = rectFromJson(dataObj["rectangle"].toArray());
}