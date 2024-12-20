#include <paint/workspace.hpp>

WorkSpace::WorkSpace(QFrame* parent)
    : QFrame(parent)
{
    setObjectName("workSpace");
}

void WorkSpace::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _startPoint = event->pos();
        _endPoint = _startPoint;

        _isDrawning = true;
        _currentShape = std::make_unique<Triangle>(_startPoint, _endPoint);
    }
}

void WorkSpace::mouseMoveEvent(QMouseEvent* event)
{
    if (_isDrawning)
    {
        _endPoint = event->pos();
        update();
    }
}

void WorkSpace::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && _isDrawning)
    {
        _endPoint = event->pos();
        _isDrawning = false;

        _shapes.push_back(std::make_unique<Triangle>(_startPoint, _endPoint));
        update();
    }
}

void WorkSpace::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto& shape: _shapes)
    {
        shape->draw(&painter);
    }

    if (_isDrawning && _currentShape)
    {
        _currentShape->drawTemporary(&painter, _startPoint, _endPoint);
    }
}