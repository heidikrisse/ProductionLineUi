#ifndef UIUPDATER_H
#define UIUPDATER_H
#include "mqtt_client.h"
#include <QObject>
#include <QThread>
#include <QMutex>


class uiUpdater : public QObject
{
    Q_OBJECT
  public:
    uiUpdater(MQTTClient *client, QObject *parent = nullptr);
    ~uiUpdater();
    void start();
  public slots:
    void on_MQTT_message_received(const json& message, const std::string& topic);
  signals:
    QMutex mutex;

  private:
    MQTTClient *client;
};

#endif // UIUPDATER_H
