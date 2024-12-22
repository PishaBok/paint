#pragma once

#include <QMouseEvent>
#include <QPainter>

class WorkSpace;
class BaseShape;

class WorkSpaceStrategy
{
public:
    WorkSpaceStrategy(WorkSpace* context);
    virtual ~WorkSpaceStrategy() = default;

    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
    virtual void drawTemporary(QPainter* painter);
protected:
    WorkSpace* _context;

    BaseShape* findShapeAt(const QPoint& pos) const; // Получить фигуру в точке
};