#include <paint/window.hpp>

Window::Window(QMainWindow* parent)
    : QMainWindow(parent)
{
    QToolBar* toolBar = createToolBar();
    _workSpace = new WorkSpace;

    addToolBar(toolBar);
    setCentralWidget(_workSpace);
    resize(800, 600);
}

QPushButton* Window::createStrategyButton(const QString& title, const StrategyButton type)
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
    QPushButton* rectButton = createStrategyButton(QString::fromUtf8("\u25A1"), StrategyButton::rectangle);
    QPushButton* triangleButton = createStrategyButton(QString::fromUtf8("\u25B2"), StrategyButton::triangle);
    QPushButton* ellipseButton = createStrategyButton(QString::fromUtf8("\u25EF"), StrategyButton::ellipse);
    QPushButton* boundButton = createStrategyButton(QString::fromUtf8("\u27CD"), StrategyButton::bound);
    QPushButton* dragButton = createStrategyButton(QString::fromUtf8("\u270B"), StrategyButton::drag);
    QPushButton* eraseButton = createStrategyButton(QString::fromUtf8("\U0001F5D1"), StrategyButton::erase);

    QPushButton* loadFileButton{new QPushButton("Загрузить")};
    connect(loadFileButton, &QPushButton::pressed, this, &Window::loadFileButtonPressed);
    QPushButton* saveFileButton{new QPushButton("Сохранить")};
    connect(saveFileButton, &QPushButton::pressed, this, &Window::saveFileButtonPressed);

    QWidget* spacer{new QWidget};
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    toolBar->addWidget(rectButton);
    toolBar->addWidget(triangleButton);
    toolBar->addWidget(ellipseButton);
    toolBar->addSeparator();
    toolBar->addWidget(boundButton);
    toolBar->addWidget(dragButton);
    toolBar->addWidget(eraseButton);
    toolBar->addSeparator();
    toolBar->addWidget(spacer);
    toolBar->addWidget(loadFileButton);
    toolBar->addWidget(saveFileButton);

    return toolBar;
}



void Window::strategyButtonPressed()
{
    StrategyButton button = _buttonMap.at(sender());
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

void Window::loadFileButtonPressed()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Открыть файл", QString(), "Paint Files (*.paintdoc);;All Files (*.*)"
    );

    if (filePath.isEmpty()) {return;} // Пользователь нажал "Отмена"

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    _workSpace->loadFromFile(file);
}

void Window::saveFileButtonPressed()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "Сохранить как", QString(), "Paint Files (*.paintdoc);;All Files (*.*)"
    );

    if (filePath.isEmpty()) {return;} // Пользователь нажал "Отмена"
    else if (!filePath.endsWith(".paintdoc", Qt::CaseInsensitive)) {filePath += ".paintdoc";} // Добавляем расширение

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    _workSpace->saveToFile(file);
}

