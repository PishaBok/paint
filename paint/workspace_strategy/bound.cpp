#include <paint/workspace_strategy/bound.hpp>
#include <paint/workspace.hpp>

BoundStrategy::BoundStrategy(WorkSpace* context)
    : WorkSpaceStrategy(context), _isDrawning{false}, _startShape{nullptr}
{}

void BoundStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!_isDrawning)
        {
            _startShape = findShapeAt(event->pos()); // Ищем фигуру под курсором
            if (_startShape)
            {
                _isDrawning = true;
                _startPos = _startShape->center(); // Начинаем с центра фигуры
                _currentPos = event->pos();
                _context->setMouseTracking(true); // Включаем отслеживание мыши
                _context->update();
                
            }
        }
        else
        {
            // Повторный клик завершает связь
            auto endShape = findShapeAt(event->pos());
            if (endShape && endShape != _startShape)
            {
                auto bound = std::make_unique<Bound>(_startShape, endShape);
                _context->addBound(std::move(bound));
            }
            endDrawning();
        }
    }
}

void BoundStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if (_isDrawning)
    {
        _currentPos = event->pos(); // Обновляем позицию курсора
        _context->update();
    }
}

void BoundStrategy::mouseReleaseEvent(QMouseEvent* event)
{}

void BoundStrategy::endDrawning()
{
    _isDrawning = false;
    _startShape = nullptr;
    _context->setMouseTracking(false); // Выключаем отслеживание мыши
    _context->update();
}

void BoundStrategy::drawTemporary(QPainter* painter)
{
    if (_isDrawning && _startShape)
    {
        painter->setPen(Qt::SolidLine);
        painter->drawLine(_startPos, _currentPos); // Рисуем временную линию
    }
}
