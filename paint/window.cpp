#include <paint/window.hpp>

Window::Window(QMainWindow* parent)
    : QMainWindow(parent)
{
    QToolBar* toolBar = createToolBar();
    _workSpace = new WorkSpace;

    addToolBar(toolBar);
    setCentralWidget(_workSpace);
    resize(600, 400);
}



QToolBar* Window::createToolBar()
{
    QToolBar* toolBar = new QToolBar;
    toolBar->setMovable(false);

    QPushButton* rectButton = new QPushButton("Прямоугольник");
    connect(rectButton, &QPushButton::clicked, [this]()
    {       
        auto strategy = std::make_unique<DrawStrategy>(_workSpace, ShapeType::rectangle);
        _workSpace->setStrategy(std::move(strategy));
    });

    QPushButton* triangleButton = new QPushButton("Треугольник");
    connect(triangleButton, &QPushButton::clicked, [this]()
    {       
        auto strategy = std::make_unique<DrawStrategy>(_workSpace, ShapeType::triangle);
        _workSpace->setStrategy(std::move(strategy));
    });

    QPushButton* boundButton = new QPushButton("Связь");
    connect(boundButton, &QPushButton::clicked, [this]()
    {       
        auto strategy = std::make_unique<BoundStrategy>(_workSpace);
        _workSpace->setStrategy(std::move(strategy));
    });

    QPushButton* dragButton = new QPushButton("Переместить");

    QPushButton* eraseButton = new QPushButton("Удалить");
    connect(eraseButton, &QPushButton::clicked, [this]()
    {       
        auto strategy = std::make_unique<EraseStrategy>(_workSpace);
        _workSpace->setStrategy(std::move(strategy));
    });

    toolBar->addWidget(rectButton);
    toolBar->addWidget(triangleButton);
    toolBar->addSeparator();
    toolBar->addWidget(boundButton);
    toolBar->addWidget(dragButton);
    toolBar->addWidget(eraseButton);

    return toolBar;
}
