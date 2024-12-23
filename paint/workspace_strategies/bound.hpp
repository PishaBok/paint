#pragma once

#include <paint/workspace_strategies/workspace_strategy.hpp>
#include <paint/shapes/bound.hpp>

class BoundStrategy: public WorkSpaceStrategy
{
public:
    BoundStrategy(WorkSpace* context);
    virtual ~BoundStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void drawTemporary(QPainter* painter) override;
    void keyPressEvent(QKeyEvent* event) override;
protected:
    void onCancel() override;
private:
    bool _isDrawning;
    BaseShape* _startShape;
    QPoint _startPos;
    QPoint _currentPos;
    QPoint _endPos;


    void handleLeftButton(QMouseEvent* event);
};