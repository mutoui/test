#include "calculatorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalculatorWidget calculator;
    calculator.show();
    return app.exec();
}
