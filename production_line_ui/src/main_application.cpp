#include "main_application.h"

main_application::main_application()
{
    ui = new MainWindow();
    client = new MQTTClient("5.tcp.eu.ngrok.io:18017", "abcd123dsa");
    client->connect();
    client->subscribe("conveyer_params");
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_width{desktop->width()};
    int screen_height{desktop->height()};

    float window_width_percentage{0.8}; // Adjust as needed
    float window_height_percentage{0.8}; // Adjust as needed
    int window_width{static_cast<int>(screen_width * window_width_percentage)};
    int window_height{static_cast<int>(screen_height * window_height_percentage)};
    ui->resize(window_width, window_height);
    ui->show();


}
