#include <QApplication>
#include <QFile>

#include <paint/window.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QFile styleFile(":/css/style.css");
    styleFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleFile.readAll());
    app.setWindowIcon(QIcon(":/img/app_icon.png"));

    Window wd;
    wd.show();

    return app.exec();
}
