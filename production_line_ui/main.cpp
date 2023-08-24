// main.cpp
#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.start_data_update_loop();
    return a.exec();
}
