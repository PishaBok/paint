#include <paint/shapes/shape_types.hpp>
#include <paint/shapes/rectangle.hpp>
#include <paint/shapes/triangle.hpp>
#include <paint/shapes/ellipse.hpp>

const std::map<ShapeType, std::function<std::unique_ptr<BaseShape>(void)>> shapeFactory =
{
    {ShapeType::rectangle, [](){return std::make_unique<Rectangle>();}},
    {ShapeType::triangle, [](){return std::make_unique<Triangle>();}},
    {ShapeType::ellipse, [](){return std::make_unique<Ellipse>();}}
};