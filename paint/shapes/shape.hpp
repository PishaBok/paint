#pragma once

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QRect>

class BaseShape
{
public:
    virtual ~BaseShape() = default;

    virtual void draw(QPainter* painter) = 0; // Рисование фигуры
    virtual bool contains(const QPoint& point) const = 0; // Проверка на содержание фигурой точки
    virtual void resize(const QRect& newBounds) = 0; // Изменение размера
    virtual void move(const QPoint& delta) = 0; // Перемещение фигуры
    virtual QPoint center() const = 0; // Получение центра фигуры
    virtual QRect boundingRect() const = 0; // Получение ограничивающего прямоугольника
} ;
