#include <paint/workspace_strategy/workspace_strategy.hpp>
#include <paint/workspace.hpp>

WorkSpaceStrategy::WorkSpaceStrategy(WorkSpace* context)
    : _context{context}
{

}

void WorkSpaceStrategy::drawTemporary(QPainter* painter) 
{

}

BaseShape* WorkSpaceStrategy::findShapeAt(const QPoint& pos) const
{   
    for (const auto& shape: _context->shapes())
    {
        if (shape->contains(pos)) {return shape.get();} // Возвращаем фигуру, если курсор внутри нее
    }
    return nullptr; // Курсор не на фигуре
}
