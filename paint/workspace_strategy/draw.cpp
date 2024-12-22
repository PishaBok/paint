#include <paint/workspace_strategy/draw.hpp>
#include <paint/workspace.hpp>

DrawStrategy::DrawStrategy(WorkSpace* context, const ShapeType type)
    : WorkSpaceStrategy(context), _type{type}, _currentShape{nullptr}, _isDrawning{false}
{}

void DrawStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _startPos = event->pos();
        _endPos = _startPos;
        _isDrawning = true;

        _currentShape = _shapeFactory.at(_type)();
    }
}

void DrawStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if (_isDrawning)
    {
        _endPos = event->pos();
        _currentShape->updateShape(_startPos, _endPos);
        _context->update();
    }
}

void DrawStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && _isDrawning)
    {
        _endPos = event->pos();
        _isDrawning = false;

        _currentShape->updateShape(_startPos, _endPos);
        _context->addShape(std::move(_currentShape));
    }
}

void DrawStrategy::drawTemporary(QPainter* painter)
{
    _currentShape->draw(painter);
}
