// main.cpp
#include "include/mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    float windowWidthPercentage = 0.8; // Adjust as needed
    float windowHeightPercentage = 0.8; // Adjust as needed
    int windowWidth = static_cast<int>(screenWidth * windowWidthPercentage);
    int windowHeight = static_cast<int>(screenHeight * windowHeightPercentage);

    w.resize(windowWidth, windowHeight);
    w.show();
    w.start_data_update_loop();
    return a.exec();
}
