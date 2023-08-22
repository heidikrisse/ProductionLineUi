// mqtt_client.cpp
#include "mqtt_client.h"

// Constructor
MQTTClient::MQTTClient(const std::string& broker_address, const std::string& client_id)
    : client(broker_address, client_id)
{
}

MQTTClient::~MQTTClient()
{
    disconnect();
}

bool MQTTClient::connect()
{
    // return client.connect();
    return true; // now to avoid error, client.connect() should return true if succeeds or false if fails to connect
}

void MQTTClient::disconnect()
{
    // client.disconnect();
}

// Function to fetch data from MQTT topics
std::vector<std::string> MQTTClient::fetch_sensor_data()
{
    std::vector<std::string> data;

    // Convert each json string to a json object and then parse it:
    for (const std::string& raw_data : data) {
        // Convert string to json object
        json j = json::parse(raw_data);
        // Parse the data and store in the cache
        data_cache.push_back(json_data::json_to_vec(j));
    }

    return data;
}

void MQTTClient::set_conveyor_speed(int speed)
{
}

void MQTTClient::set_heating_elements(std::vector<bool> states)
{
}

void MQTTClient::set_cooling_system(bool state)
{
}

void MQTTClient::set_quality_control_camera(bool state)
{
}

// Function to calculate the failure rate from the fetched data
double MQTTClient::get_failure_rate() const
{
    double total_units{0};
    double failed_units{0};

        for (const auto& data : data_cache) {
            total_units += data.units_per_minute;
            // failed_units += data.failed_qc_units;
        }

        return failed_units / total_units;
}

// Function to calculate the operating costs from the fetched data
double MQTTClient::get_operating_cost() const
{
    double cost_per_unit{0.1}; // <= can be changed
    // Cost for every heater turned on / unit time
    double heater_cost{3}; // <= can be changed
    // Const for cooler turned on / unit time
    double cooler_cost{5}; // <= can be changed

    double total_units{0};
    double total_cost{0};

    for (const auto& data : data_cache)
    {
        total_units += data.units_per_minute;
        total_cost += data.units_per_minute * cost_per_unit;

        if (data.heater1_status)
        {
            total_cost += heater_cost;
        }

        if (data.heater2_status)
        {
            total_cost += heater_cost;
        }

        if (data.heater3_status)
        {
            total_cost += heater_cost;
        }

        if (data.cooler_status)
        {
            total_cost += cooler_cost;
        }

    }

    return total_cost / total_units;
}

// Function to save the data to a file
void MQTTClient::save_data_to_file(const std::string& filename)
{
    // Open the file in append mode so that it doesn't overwrite the file if it already exists
    std::ofstream out_file(filename, std::ios::app);

    if (out_file.is_open())
    {
        for (const auto& data : data_cache)
        {
            json j;

            j["timestamp"] = data.timestamp;
            j["conveyor_speed"] = data.units_per_minute;
            j["heater1"] = data.heater1_status;
            j["heater2"] = data.heater2_status;
            j["heater3"] = data.heater3_status;
            j["cooler"] = data.cooler_status;
            j["qc_camera"] = data.qc_camera_status;

            for (int i{0}; i < 10; ++i)
            {
                std::string sensor_name = "temp_sensor" + std::to_string(i+1);
                j[sensor_name] = data.heat_sensors[i];
            }

            out_file << j.dump(4) << '\n';
        }

        out_file.close();
    }
}
