#pragma once

#include <paint/workspace_strategies/workspace_strategy.hpp>
#include <paint/shapes/base_shape.hpp>

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
    QRect _originalPosition;
    QPoint _lastMousePos;
};