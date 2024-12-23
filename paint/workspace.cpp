#include <paint/workspace.hpp>

WorkSpace::WorkSpace(QFrame* parent)
    : QFrame(parent), _strategy{nullptr}
{
    setObjectName("workSpace");
    setFocusPolicy(Qt::ClickFocus);
}

void WorkSpace::setStrategy(std::unique_ptr<WorkSpaceStrategy> strategy)
{
    _strategy = std::move(strategy);
}

void WorkSpace::addShape(std::unique_ptr<BaseShape> shape)
{
    _shapes.push_back(std::move(shape));
}

void WorkSpace::removeShape(BaseShape* shapeToRemove)
{
    auto it = std::find_if(_shapes.begin(), _shapes.end(),
        [shapeToRemove](const std::unique_ptr<BaseShape>& shape) {
            return shape.get() == shapeToRemove;
    });

    if (it != _shapes.end()) {_shapes.erase(it);}
}

void WorkSpace::addBound(std::unique_ptr<Bound> bound)
{
    _bounds.push_back(std::move(bound));
}

void WorkSpace::removeBoundsIf(const std::function<bool(const std::unique_ptr<Bound>&)>& predicate)
{
    _bounds.erase(std::remove_if(_bounds.begin(), _bounds.end(), predicate), _bounds.end());
}

const std::vector<std::unique_ptr<BaseShape>>& WorkSpace::shapes() const
{
    return _shapes;
}

const std::vector<std::unique_ptr<Bound>>& WorkSpace::bounds() const
{
    return _bounds;
}

void WorkSpace::mousePressEvent(QMouseEvent* event)
{
    if (_strategy) {_strategy->mousePressEvent(event);}
}

void WorkSpace::mouseMoveEvent(QMouseEvent* event)
{
    if (_strategy) _strategy->mouseMoveEvent(event);
}

void WorkSpace::mouseReleaseEvent(QMouseEvent* event)
{
    if (_strategy) _strategy->mouseReleaseEvent(event);
}

void WorkSpace::keyPressEvent(QKeyEvent* event)
{
    if (_strategy) {_strategy->keyPressEvent(event);}
}

void WorkSpace::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    // Рисуем фигуры
    for (auto& shape: _shapes)
    {
        shape->draw(&painter);
    }

    // Рисуем связи
    for (auto& bound: _bounds)
    {
        bound->draw(&painter);
    }

    // Рисуем временную форму 
    if (_strategy) {_strategy->drawTemporary(&painter);} 
}