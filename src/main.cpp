#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("易医科普"));
    MainWindow window;
    window.show();
    return app.exec();
}
