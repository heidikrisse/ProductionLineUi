// mqtt_client.h
#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "mqtt/async_client.h"
#include "json.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <QObject>

using json = nlohmann::json;

/**
 * MQTTClient class is a wrapper around the Paho MQTT async client.
 * - connects to an MQTT broker, fetches data, controls a production
 * line.
 */

class MainWindow;
struct CurrentConveyorData{
    std::string time_stamp = "0000-00-00T00:00:00GMT+2";
    bool conveyor_manual_control = false;
    bool heater1_manual_control = false;
    bool heater2_manual_control = false;
    bool heater3_manual_control = false;
    bool cooler_manual_control = false;
    bool qc_camera_toggle = false;
    int qc_camera_fails = 0;
    int conveyor_upm = 423;
    bool heater1 = false;
    bool heater2 = false;
    bool heater3 = false;
    bool cooler = false;

    std::array<float, 10> temps {1,2,3,4,5,6,7,8,9,10};
};

class MQTTClient : public QObject, public mqtt::callback
{
    Q_OBJECT
public:
    MQTTClient(const std::string& broker_address, const std::string& client_id);
    ~MQTTClient();

    CurrentConveyorData curr_data;

    std::vector<CurrentConveyorData> data_cache; // from database

    // Function to connect to the MQTT broker
    bool connect();

    // Function to disconnect from the MQTT broker
    void disconnect();

    // Subscribe to topic
    void subscribe(const std::string& topic);

    // Send json's to broker
    void publish(const std::string& topic, const std::string& payload);

    // Function to fetch latest data from the sensors
    std::vector<std::string> fetch_sensor_data();

    // Overriden callback function to handle incoming messages
    virtual void message_arrived(mqtt::const_message_ptr msg) override;

    // Function to calculate the failure rate from the fetched data
    double get_failure_rate() const;
    // Function to calculate the operating costs from the fetched data
    std::pair<double, double>get_operating_cost() const;
    // Function to calculate the average temperature of the fetched data
    double get_average_temperature() const;
    int get_average_upm() const;
    void update_analytics_values();
    void publish_data();
    uint8_t current_mw_tab = 1;
    int conveyor_desired_speed = 0;

  private: signals:

    void conveyor_speed_changed(int new_speed);
    void conveyor_control(bool state);
    void heater_controls(bool heater1, bool heater2, bool heater3);
    void heater_states(bool heater1, bool heater2, bool heater3);
    void cooler_state(bool state);
    void cooler_control(bool state);
    void qc_camera_state(bool state);
    void temps_changed(std::array<float,10> temps);
    void db_updated(CurrentConveyorData& data);
    void analytics_data_updated();

private:
    mqtt::async_client client;
};

#endif
