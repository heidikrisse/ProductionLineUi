// mqtt_client.h
#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "mqtt/async_client.h"
#include "json_parser.h" // for using nlohmann::json

#include <fstream>
#include <string>
#include <vector>

/**
 * MQTTClient class is a wrapper around the Paho MQTT async client.
 * - connects to an MQTT broker, fetches data, controls a production
 * line and save data to a file.
 */

class MQTTClient : public mqtt::callback
{
public:
    MQTTClient(const std::string& broker_address, const std::string& client_id);
    ~MQTTClient();

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

    std::vector<json_data::parsed_json> load_sample_data(const std::string& folder_path);

    // Function to control production line
    void set_conveyor_speed(int units_per_minute);
    void set_heating_elements(std::vector<bool> states);
    void set_cooling_system(bool state);
    void set_quality_control_camera(bool state);

    // Overriden callback function to handle incoming messages
    virtual void message_arrived(mqtt::const_message_ptr msg) override;

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

