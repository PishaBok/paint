#pragma once

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPolygon>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include <paint/shapes/shape_types.hpp>

class BaseShape
{
public:
    BaseShape(ShapeType type);
    virtual ~BaseShape() = default;

    virtual void draw(QPainter* painter) = 0; // Рисование фигуры
    virtual bool contains(const QPoint& point) const = 0; // Проверка на содержание фигурой точки
    virtual void resize(const QRect& newBounds) = 0; // Изменение размера
    virtual void move(const QPoint& delta) = 0; // Перемещение фигуры
    virtual QPoint center() const = 0; // Получение центра фигуры
    virtual QRect boundingRect() const = 0; // Получение ограничивающего прямоугольника
    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& jsonObj) = 0;

    QString id() const {return _id;}
protected:
    QString _id;
    ShapeType _type;

    // Поддержка Json для QRect
    QJsonArray rectToJson(const QRect& rect) const;
    QRect rectFromJson(const QJsonArray& jsonArray) const;
    // Поддержка Json для QPolygon
    QJsonArray polygonToJson(const QPolygon& polygon) const;
    QPolygon polygonFromJson(const QJsonArray& jsonArray) const;

private:
    static QString generateId()
    {
        static int counter{0};
        return QString("shape_%1").arg(++counter);
    }
} ;
