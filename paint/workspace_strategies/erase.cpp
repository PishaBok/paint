#include <paint/workspace_strategies/erase.hpp>
#include <paint/workspace.hpp>

EraseStrategy::EraseStrategy(WorkSpace* context)
    : WorkSpaceStrategy(context)
{}

void EraseStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto shape = findShapeAt(event->pos());
        // Если фигура найдена, удаляем ее и обновляем контекст
        if (shape)
        {   
            // Очищаем все связанные с shape связи
            _context->removeBoundsIf([&](const std::unique_ptr<BoundLine>& bound)
                {return bound->isUsedByShape(shape);});

            _context->removeShape(shape); // Удаляем фигуру
            _context->update(); // Обновляем рабочуб область
        }
    }
}

void EraseStrategy::mouseMoveEvent(QMouseEvent* event)
{}

void EraseStrategy::mouseReleaseEvent(QMouseEvent* event)
{}

void EraseStrategy::keyPressEvent(QKeyEvent* event)
{}
