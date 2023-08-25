// mqtt_main_window_bridge.h
#ifndef MQTT_MAIN_WINDOW_BRIDGE_H
#define MQTT_MAIN_WINDOW_BRIDGE_H

#include "mainwindow.h"
#include "mqtt_client.h"

#include <QObject>
#include <QTimer>

class MqttMainWindowBridge : public QObject
{
    Q_OBJECT

public:
    MqttMainWindowBridge(MainWindow* mainWindow, MQTTClient* mqttClient, QObject* parent = nullptr);

public slots:
    void updateFromMqtt();
    void updateFromUI();

private:
    MainWindow* mainWindow;
    MQTTClient* mqttClient;
    QTimer* updateTimer;
};

#endif
