#pragma once

#include <QDebug>
#include <paint/shapes/shape.hpp>

class Bound: public BaseShape
{
public:
    Bound(BaseShape* start, BaseShape* end);
    virtual ~Bound() = default;

    void draw(QPainter* painter) override;

    bool contains(const QPoint& point) const override {}; // Проверка на содержание фигурой точки
    void resize(const QRect& newBounds) override {}; // Изменение размера
    void move(const QPoint& delta) override {}; // Перемещение фигуры
    QPoint center() const override {}; // Получение центра фигуры
    QRect boundingRect() const override {}; // Получение ограничивающего прямоугольника

    bool isUsedByShape(BaseShape* shape) const;
private:
    BaseShape* _start;
    BaseShape* _end;
};