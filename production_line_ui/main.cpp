// main.cpp
#include "include/mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_width{desktop->width()};
    int screen_height{desktop->height()};

    float window_width_percentage{0.8}; // Adjust as needed
    float window_height_percentage{0.8}; // Adjust as needed
    int window_width{static_cast<int>(screen_width * window_width_percentage)};
    int window_height{static_cast<int>(screen_height * window_height_percentage)};

    w.resize(window_width, window_height);
    w.show();
    w.start_data_update_loop();
    return a.exec();
}
