#pragma once

#include <paint/workspace_strategy/workspace_strategy.hpp>
#include <paint/shapes/shape.hpp>

class DragStrategy: public WorkSpaceStrategy
{
public:
    DragStrategy(WorkSpace* context);
    virtual ~DragStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
protected:
    void onCancel() override;
private:
    bool _isDragging;
    BaseShape* _selectedShape;
    QPoint _lastMousePos;
};