// mqtt_client.h
#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "mqtt/async_client.h"
#include <fstream>
#include "json_parser.h" // for using nlohmann::json
#include <string>
#include <vector>

/**
 * MQTTClient class is a wrapper around the Paho MQTT async client.
 * - connects to an MQTT broker, fetches data, controls a production
 * line and save data to a file.
 */

class MQTTClient
{
public:
    MQTTClient(const std::string& brokerAddress, const std::string& clientId);
    ~MQTTClient();

    // Function to connect to the MQTT broker
    bool connect();

    // Function to disconnect from the MQTT broker
    void disconnect();

    // Function to fetch latest data from the sensors
    std::vector<std::string> fetch_sensor_data();

    // Function to control production line
    void set_production_line_speed(int speed);
    void set_heating_elements(std::vector<bool> states);
    void set_cooling_system(bool state);
    void set_quality_control_camera(bool state);

    // Function to calculate the failure rate from the fetched data
    double get_failure_rate() const;
    // Function to calculate the operating costs from the fetched data
    double get_operating_cost() const;

    // Function to save data to a file
    void save_data_to_file(const std::string& filename);

private:
    mqtt::async_client client;
    std::vector<json_data::parsed_json> data_cache;
};

#endif

