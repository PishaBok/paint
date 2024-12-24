#pragma once

#include <paint/shapes/base_shape.hpp>

class Rectangle: public BaseShape
{
public:
    Rectangle(const QRect& rect = {});
    virtual ~Rectangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& jsonObj) override;
private:
    QRect _rect;
};