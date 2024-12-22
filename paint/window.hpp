#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>

#include <paint/workspace.hpp>

class Window: public QMainWindow
{
    Q_OBJECT
public:
    Window(QMainWindow* parent = nullptr);

private:
    WorkSpace* _workSpace;

    QToolBar* createToolBar();
};