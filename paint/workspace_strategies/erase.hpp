#pragma once

#include <paint/workspace_strategies/workspace_strategy.hpp>


class EraseStrategy: public WorkSpaceStrategy
{
public:
    EraseStrategy(WorkSpace* context);
    virtual ~EraseStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};