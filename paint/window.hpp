#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>

#include <paint/workspace.hpp>

enum class Button
{
    rectangle,
    triangle,
    ellipse,
    bound,
    drag,
    erase
};

class Window: public QMainWindow
{
    Q_OBJECT
public:
    Window(QMainWindow* parent = nullptr);
private:
    WorkSpace* _workSpace;
    std::map<QObject*, Button> _buttonMap;
    std::map<Button, std::function<std::unique_ptr<WorkSpaceStrategy>(void)>> _strategyFactory
    {
        {Button::rectangle, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::rectangle);}},
        {Button::triangle, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::triangle);}},
        {Button::ellipse, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::ellipse);}},
        {Button::bound, [this](){return std::make_unique<BoundStrategy>(_workSpace);}},
        {Button::drag, [this](){return std::make_unique<DragStrategy>(_workSpace);}},
        {Button::erase, [this](){return std::make_unique<EraseStrategy>(_workSpace);}}
    }; 


    QPushButton* createButton(const QString& title, const Button type); // Создание кнопки
    QToolBar* createToolBar(); // Создание туллбара
private slots:
    void strategyButtonPressed(); // Смена режима в WorkSpace
    void buttonHighlighter(); // Подсветка активированной кнопки
};