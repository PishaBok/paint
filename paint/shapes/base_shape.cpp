#include <paint/shapes/base_shape.hpp>

BaseShape::BaseShape(ShapeType type) 
    : _type{type}, _id{generateId()} 
{}

QJsonArray BaseShape::rectToJson(const QRect& rect) const
{
    QJsonArray jsonArray;
    jsonArray.append(rect.x());
    jsonArray.append(rect.y());
    jsonArray.append(rect.width());
    jsonArray.append(rect.height());
    return jsonArray;
}

QRect BaseShape::rectFromJson(const QJsonArray& jsonArray) const
{
    if (jsonArray.size() != 4) {return QRect();}

    return QRect(
        jsonArray[0].toInt(),
        jsonArray[1].toInt(),
        jsonArray[2].toInt(),
        jsonArray[3].toInt()
    );
}

QJsonArray BaseShape::polygonToJson(const QPolygon& polygon) const
{
    QJsonArray polygonArray;

    for (const QPoint& point: polygon)
    {
        QJsonArray pointArray;
        pointArray.append(point.x());
        pointArray.append(point.y());
        polygonArray.append(pointArray);
    }

    return polygonArray;
}

QPolygon BaseShape::polygonFromJson(const QJsonArray& jsonArray) const
{
    QPolygon polygon;

    for (const auto& value: jsonArray)
    {
        QJsonArray pointArray = value.toArray();
        if (pointArray.size() == 2)
        {
            QPoint point{pointArray[0].toInt(), pointArray[1].toInt()};
            polygon.append(point);
        }
    }
    
    return polygon;
}