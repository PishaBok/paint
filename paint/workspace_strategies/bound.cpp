#include <paint/workspace_strategies/bound.hpp>
#include <paint/workspace.hpp>

BoundStrategy::BoundStrategy(WorkSpace* context)
    : WorkSpaceStrategy(context), _isDrawning{false}, _startShape{nullptr}
{}

void BoundStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {handleLeftButton(event);} // Обрабатываем нажатие левой кнопки
    else if (event->button() == Qt::RightButton) {onCancel();}  // Если была нажата правая кнопка мыши - отменяем рисование
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

void BoundStrategy::keyPressEvent(QKeyEvent* event)
{
    if (_isDrawning && event->key() == Qt::Key_Escape) {onCancel();}
}

void BoundStrategy::handleLeftButton(QMouseEvent* event)
{
    if (!_isDrawning)
    {
        _startShape = findShapeAt(event->pos()); // Ищем фигуру под курсором
        if (_startShape)
        {
            _isDrawning = true;
            _startPos = _startShape->center(); // Начинаем с центра фигуры
            _currentPos = event->pos();
            _context->setMouseTracking(true);
            _context->update();  
        }
    }
    else  
    {   // Повторный клик завершает связь
        auto endShape = findShapeAt(event->pos());
        if (endShape && endShape != _startShape)
        {
            auto bound = std::make_unique<BoundLine>(_startShape, endShape);
            _context->addBound(std::move(bound));
        }
        onCancel();
    }
}

void BoundStrategy::onCancel()
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
