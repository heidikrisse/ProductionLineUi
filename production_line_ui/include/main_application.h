#ifndef MAIN_APPLICATION_H
#define MAIN_APPLICATION_H

#include <QObject>
#include "mainwindow.h"
#include "mqtt_client.h"
class main_application : public QObject
{
    Q_OBJECT
  public:
    main_application();

  private:
    MainWindow* ui;
    MQTTClient* client;
};

#endif // MAIN_APPLICATION_H
