#pragma once

#include <map>
#include <functional>
#include <memory>

class BaseShape;

enum class ShapeType
{
    rectangle,
    triangle,
    ellipse,
    bound
};

extern const std::map<ShapeType, std::function<std::unique_ptr<BaseShape>(void)>> shapeFactory;
