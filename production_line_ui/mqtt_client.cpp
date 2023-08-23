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
    mqtt::connect_options conn_opts;
    try{
        client.connect(conn_opts)->wait();
        return true;
    } catch(const mqtt::exception& e){
        std::cerr << "connection error: " << e.what() << '\n';
        return false;
    }
}

void MQTTClient::disconnect()
{
    try{
        client.disconnect()->wait();
    } catch (const mqtt::exception& e){
        std::cerr << "disconnect error: " << e.what() << '\n';
    }
}

void MQTTClient::subscribe(const std::string& topic){
    try{
        client.subscribe(topic, 0)->wait();
    } catch (const mqtt::exception& e){
        std::cerr << "subscripe Error: " << e.what() << '\n';
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& payload){
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(0);

    try{
        client.publish(msg)->wait();
    }catch (const mqtt::exception& e){
        std::cerr << "publish Error: " << e.what() << '\n';
    }
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

void MQTTClient::on_message(const mqtt::message* message){
    // std::string payload = message->get_payload_str();
    // json j = json::parse(payload);
    // data_cache.push_back(json_data::json_to_vec(j));
    assert(0); // just for testing
}

void MQTTClient::set_conveyor_speed(int units_per_minute)
{
    std::string payload = std::to_string(units_per_minute);
    publish("test_topic_123" , payload);
}

void MQTTClient::set_heating_elements(std::vector<bool> states)
{
    json j;
    j["heater1"] = states[0];
    j["heater2"] = states[1];
    j["heater3"] = states[2];
    publish("heater_states_topic", j.dump());
}

void MQTTClient::set_cooling_system(bool state)
{
    json j;
    j["cooler"] = state;
    publish("cooler_state_topic", j.dump());
}

void MQTTClient::set_quality_control_camera(bool state)
{
    json j;
    j["qc_camera"] = state;
    publish("qc_camera_ctate_topic", j.dump());
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
