#pragma once

#include <map>
#include <QPoint>

#include <paint/workspace_strategies/workspace_strategy.hpp>
#include <paint/shapes/rectangle.hpp>
#include <paint/shapes/triangle.hpp>
#include <paint/shapes/ellipse.hpp>

class DrawStrategy: public WorkSpaceStrategy
{
public:
    DrawStrategy(WorkSpace* context, const ShapeType type);
    virtual ~DrawStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void drawTemporary(QPainter* painter) override;
protected:
    void onCancel() override;
private:
    ShapeType _type;

    std::unique_ptr<BaseShape> _currentShape;
    QPoint _startPos;
    QPoint _endPos;
    bool _isDrawning;
};