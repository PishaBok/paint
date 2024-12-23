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

QPushButton* Window::createButton(const QString& title, const Button type)
{
    QPushButton* button{new QPushButton(title)};
    button->setCheckable(true);

    connect(button, &QPushButton::clicked, this, &Window::strategyButtonPressed);
    connect(button, &QPushButton::clicked, this, &Window::buttonHighlighter);
    _buttonMap[button] = type;
    

    return button;
}


QToolBar* Window::createToolBar()
{
    QToolBar* toolBar = new QToolBar;
    toolBar->setMovable(false);

    // Создание кнопок
    QPushButton* rectButton = createButton(QString::fromUtf8("\u25A1"), Button::rectangle);
    QPushButton* triangleButton = createButton(QString::fromUtf8("\u25B2"), Button::triangle);
    QPushButton* ellipseButton = createButton(QString::fromUtf8("\u25EF"), Button::ellipse);
    QPushButton* boundButton = createButton(QString::fromUtf8("\u27CD"), Button::bound);
    QPushButton* dragButton = createButton(QString::fromUtf8("\u270B"), Button::drag);
    QPushButton* eraseButton = createButton(QString::fromUtf8("\U0001F5D1"), Button::erase);

    toolBar->addWidget(rectButton);
    toolBar->addWidget(triangleButton);
    toolBar->addWidget(ellipseButton);
    toolBar->addSeparator();
    toolBar->addWidget(boundButton);
    toolBar->addWidget(dragButton);
    toolBar->addWidget(eraseButton);

    return toolBar;
}



void Window::strategyButtonPressed()
{
    Button button = _buttonMap.at(sender());
    auto strategy = _strategyFactory.at(button)();

    _workSpace->setStrategy(std::move(strategy)); // Меняем стратегию в рабочем пространстве
}

void Window::buttonHighlighter()
{
    // Выключаем подсветку всех кнопок
    for (auto buttonPair: _buttonMap)
    {
        QPushButton* buttonPtr = qobject_cast<QPushButton*>(buttonPair.first);
        buttonPtr->setChecked(false);
    }

    // Включаем у кнопки-sender
    QPushButton* senderBut = qobject_cast<QPushButton*>(sender());
    senderBut->setChecked(true);
}