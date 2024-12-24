#include <paint/shapes/ellipse.hpp>

Ellipse::Ellipse(const QRect& rect)
    : BaseShape(ShapeType::ellipse), _rect{rect}
{}

void Ellipse::draw(QPainter* painter)
{
    painter->drawEllipse(_rect);
}

bool Ellipse::contains(const QPoint& point) const
{
    QPoint center = _rect.center();
    qreal rx = _rect.width() / 2.0;
    qreal ry = _rect.height() / 2.0;
    qreal dx = point.x() - center.x();
    qreal dy = point.y() - center.y();
       
    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1;   // Проверяем попадание с учетом уравнения эллипса
}

void Ellipse::resize(const QRect& newBounds)
{
    _rect = newBounds;
}

void Ellipse::move(const QPoint& delta)
{
    _rect.translate(delta);
}

QPoint Ellipse::center() const
{
    return _rect.center();
}

QRect Ellipse::boundingRect() const
{
    return _rect;
}

QJsonObject Ellipse::serialize() const
{
    QJsonObject ellipseObj;
    ellipseObj["id"] = _id;
    ellipseObj["type"] = static_cast<int>(_type);
    
    QJsonObject dataObj;
    dataObj["rectangle"] = rectToJson(_rect);

    ellipseObj["data"] = dataObj;

    return ellipseObj;
}

void Ellipse::deserialize(const QJsonObject& jsonObj)
{
    _id = jsonObj["id"].toString();
    _type = static_cast<ShapeType>(jsonObj["type"].toInt());

    QJsonObject dataObj = jsonObj["data"].toObject();
    _rect = rectFromJson(dataObj["rectangle"].toArray());
}
