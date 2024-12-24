#include <paint/workspace_strategies/draw.hpp>
#include <paint/workspace.hpp>

DrawStrategy::DrawStrategy(WorkSpace* context, const ShapeType type)
    : WorkSpaceStrategy(context), _type{type}, _currentShape{nullptr}, _isDrawning{false}
{}

void DrawStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) // Начинаем рисование фигуры
    {
        _startPos = event->pos();
        _endPos = _startPos;
        _isDrawning = true;
        _currentShape = shapeFactory.at(_type)();
    }
    else if (event->button() == Qt::RightButton) {onCancel();} // Если была нажата правая кнопка мыши - отменяем рисование
}

void DrawStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if (_isDrawning)
    {
        _endPos = event->pos();
        _currentShape->resize(QRect(_startPos, _endPos));
        _context->update();
    }
}

void DrawStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    if (_isDrawning)
    {
        _endPos = event->pos();
        _context->addShape(std::move(_currentShape));
        _isDrawning = false;
    }
}

void DrawStrategy::keyPressEvent(QKeyEvent* event)
{
    if (_isDrawning && event->key() == Qt::Key_Escape) {onCancel();}
} 

void DrawStrategy::drawTemporary(QPainter* painter)
{
    if (_isDrawning) {_currentShape->draw(painter);}
}

void DrawStrategy::onCancel()
{
    _isDrawning = false;
    _currentShape = nullptr;
    _context->update();
}
