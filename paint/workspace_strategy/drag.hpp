#pragma once

#include <paint/workspace_strategy/workspace_strategy.hpp>

class DragStrategy: public WorkSpaceStrategy
{
public:
    virtual ~DragStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override
    {

    }
    void mouseMoveEvent(QMouseEvent* event) override
    {

    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {

    }
};