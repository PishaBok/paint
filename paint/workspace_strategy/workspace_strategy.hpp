#pragma once

#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>

class WorkSpace;
class BaseShape;

class WorkSpaceStrategy
{
public:
    WorkSpaceStrategy(WorkSpace* context);
    virtual ~WorkSpaceStrategy() = default;

    // Отслеживание действий мыши и нажатых клавиш
    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    // Отрисовка временного результата (если необходимо)
    virtual void drawTemporary(QPainter* painter);
protected:
    WorkSpace* _context;

    virtual void onCancel(); // Прерываение операции
    BaseShape* findShapeAt(const QPoint& pos) const; // Получить фигуру в точке
};