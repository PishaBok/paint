#pragma once

#include <vector>
#include <QFrame>
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include <paint/workspace_strategies/draw.hpp>
#include <paint/workspace_strategies/drag.hpp>
#include <paint/workspace_strategies/bound.hpp>
#include <paint/workspace_strategies/erase.hpp>


class WorkSpace: public QFrame
{
    Q_OBJECT
public:
    WorkSpace(QFrame* parent = nullptr);

    void setStrategy(std::unique_ptr<WorkSpaceStrategy> strategy); // Установить стратегию
    void addShape(std::unique_ptr<BaseShape> shape);  // Добавить фигуру
    void removeShape(BaseShape* shapeToRemove); // Удалить фигуру
    void addBound(std::unique_ptr<Bound> bound); // Добавить связь
    void removeBoundsIf(const std::function<bool(const std::unique_ptr<Bound>&)>& predicate); // Удаляем связи соответсвующие предикату
    const std::vector<std::unique_ptr<BaseShape>>& shapes() const; // Получить фигуры
    const std::vector<std::unique_ptr<Bound>>& bounds() const; // Получить связи
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

private:
    std::unique_ptr<WorkSpaceStrategy> _strategy; // Текущая стратегия

    std::vector<std::unique_ptr<BaseShape>> _shapes; // Фигуры
    std::vector<std::unique_ptr<Bound>> _bounds;  // Связи
};