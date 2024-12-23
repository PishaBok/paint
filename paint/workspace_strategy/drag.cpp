#include <paint/workspace_strategy/drag.hpp>
#include <paint/workspace.hpp>

DragStrategy::DragStrategy(WorkSpace* context)
    : WorkSpaceStrategy(context), _isDragging{false}, _selectedShape{nullptr}
{}

void DragStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _selectedShape = findShapeAt(event->pos());
        if (_selectedShape) // Если фигура нашлась - начинаем перетаскивание
        {
            _lastMousePos = event->pos();
            _isDragging = true;
        }
    }
    else if (event->button() == Qt::RightButton) {onCancel();} // Если была нажата правая кнопка мыши - отменяем перетаскивание
}

void DragStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if (_isDragging)
    {
        QPoint delta = event->pos() - _lastMousePos;
        _selectedShape->move(delta);
        _lastMousePos = event->pos();

        _context->update();
    }
}

void DragStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    _isDragging = false;
    _selectedShape = nullptr;
}

void DragStrategy::keyPressEvent(QKeyEvent* event)
{
    if (_isDragging && event->key() == Qt::Key_Escape) {onCancel();}
}


void DragStrategy::onCancel()
{
    _isDragging = false;
    _selectedShape = nullptr;
}