#pragma once

#include <QDebug>
#include <paint/shapes/base_shape.hpp>

class BoundLine: public BaseShape
{
public:
    BoundLine(BaseShape* start, BaseShape* end);
    virtual ~BoundLine() = default;

    // Рисуем связь
    void draw(QPainter* painter) override;
    // В текущей реализации данные методы BaseShape для Bound не используются
    bool contains(const QPoint& point) const override {return false;}
    void resize(const QRect& newBounds) override {}
    void move(const QPoint& delta) override {} 
    QPoint center() const override {return QPoint();} 
    QRect boundingRect() const override {return QRect();} 
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& jsonObj) override;

    bool isUsedByShape(BaseShape* shape) const; // Проверяем используется-ли связь фигурой
private:
    BaseShape* _start;
    BaseShape* _end;
};