#include <paint/window.hpp>

Window::Window(QMainWindow* parent)
    : QMainWindow(parent)
{
    QToolBar* toolBar = createToolBar();
    WorkSpace* wspace = new WorkSpace;

    addToolBar(toolBar);
    setCentralWidget(wspace);
    resize(600, 400);
}



QToolBar* Window::createToolBar()
{
    QToolBar* toolBar = new QToolBar;
    toolBar->setMovable(false);

    QPushButton* rectButton = new QPushButton("Прямоугольник");
    connect(rectButton, &QPushButton::clicked, this, &Window::drawShape);

    toolBar->addWidget(rectButton);

    return toolBar;
}


void Window::drawShape()
{
    
}