#include "mainwindow.h"
#include "client.h"
#include "materiele.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();


    return a.exec();
}
