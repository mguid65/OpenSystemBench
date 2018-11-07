#include "headers/configwindow.h"
#include <QApplication>

/*
 * Main creates an instance of ConfigWindow and shows it.
 * Matthew Guidry 2018
 */
int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    ConfigWindow w;
    w.show();

    return a.exec();
}
