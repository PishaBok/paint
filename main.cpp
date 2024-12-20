#include <QApplication>
#include <QFile>

#include <paint/window.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QFile styleFile(":/css/style.css");
    styleFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleFile.readAll());

    Window wd;
    wd.show();

    return app.exec();
}