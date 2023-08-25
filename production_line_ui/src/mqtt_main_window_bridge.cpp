// mqtt_main_window_bridge.cpp
#include "../include/mqtt_main_window_bridge.h"
#include "../include/mainwindow.h"
#include "../include/mqtt_client.h"
#include "../ui_mainwindow.h"

#include <QSlider>
#include <QCheckBox>
#include <QPushButton>

MqttMainWindowBridge::MqttMainWindowBridge(MainWindow* mainWindow, MQTTClient* mqttClient, QObject* parent)
    : QObject(parent), mainWindow(mainWindow), mqttClient(mqttClient)
{
    // Connect UI elements to the bridge
    connect(mainWindow->ui->conveyer_units_per_minute_slider, &QSlider::valueChanged, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->pushButton_2, &QPushButton::clicked, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->heater2_manual_automatic, &QCheckBox::toggled, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->heater3_manual_automatic, &QCheckBox::toggled, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->cooler_manual_auto, &QCheckBox::toggled, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->speed_manual_or_auto, &QCheckBox::toggled, this, &MqttMainWindowBridge::updateFromUI);
    connect(mainWindow->ui->checkBox, &QCheckBox::toggled, this, &MqttMainWindowBridge::updateFromUI);
    // jne.

    // Setup a timer to periodically fetch MQTT data
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MqttMainWindowBridge::updateFromMqtt);
    updateTimer->start(1000); // update every 1 second // <= CAN BE CHANGED
}

void MqttMainWindowBridge::updateFromMqtt()
{
    // Fetch data from MQTT and update UI
    std::vector<std::string> sensorData = mqttClient->fetch_sensor_data();
    // Convert this data to suitable format and update UI, e.g.
    mainWindow->ui->pushButton->setText(QString::fromStdString(sensorData[0]));
    mainWindow->ui->pushButton_2->setText(QString::fromStdString(sensorData[0]));
    // jne.
}

void MqttMainWindowBridge::updateFromUI()
{
    // Fetch data from UI and send to MQTT
    int conveyerSpeed = mainWindow->ui->conveyer_units_per_minute_slider->value();
    mqttClient->conveyer_upm = conveyerSpeed;
    mqttClient->heater1_manual_control = mainWindow->ui->heater1_manual_automatic->isChecked();
    mqttClient->heater2_manual_control = mainWindow->ui->heater2_manual_automatic->isChecked();
    mqttClient->heater3_manual_control = mainWindow->ui->heater3_manual_automatic->isChecked();
    mqttClient->cooler_manual_control = mainWindow->ui->cooler_manual_auto->isChecked();
    // jne.

        mqttClient->publish_data();

    mqttClient->publish_data();
}
