#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include <QFileDialog>

#include <paint/workspace.hpp>

enum class StrategyButton
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
    std::map<QObject*, StrategyButton> _buttonMap;
    std::map<StrategyButton, std::function<std::unique_ptr<WorkSpaceStrategy>(void)>> _strategyFactory
    {
        {StrategyButton::rectangle, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::rectangle);}},
        {StrategyButton::triangle, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::triangle);}},
        {StrategyButton::ellipse, [this](){return std::make_unique<DrawStrategy>(_workSpace, ShapeType::ellipse);}},
        {StrategyButton::bound, [this](){return std::make_unique<BoundStrategy>(_workSpace);}},
        {StrategyButton::drag, [this](){return std::make_unique<DragStrategy>(_workSpace);}},
        {StrategyButton::erase, [this](){return std::make_unique<EraseStrategy>(_workSpace);}}
    }; 


    QPushButton* createStrategyButton(const QString& title, const StrategyButton type); // Создание кнопки
    QToolBar* createToolBar(); // Создание туллбара
private slots:
    void strategyButtonPressed(); // Смена режима в WorkSpace
    void loadFileButtonPressed();
    void saveFileButtonPressed();
    void buttonHighlighter(); // Подсветка активированной кнопки
};