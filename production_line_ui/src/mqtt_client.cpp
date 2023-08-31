// mqtt_client.cpp
#include "../include/mqtt_client.h"

#include <string>

// Add a message callback to mqtt client
MQTTClient::MQTTClient(const std::string& broker_address, const std::string& client_id)
    : client(broker_address, client_id)
{
    // Set a message callback
    client.set_callback(*this);
}

MQTTClient::~MQTTClient()
{
    disconnect();
}

bool MQTTClient::connect()
{
    mqtt::connect_options conn_opts;
    try
    {
        client.connect(conn_opts)->wait();
        std::cout << "Successfully connected to MQTT broker.\n";
        return true;
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "Connection error: " << e.what() << '\n';
        return false;
    }
}

void MQTTClient::disconnect()
{
    try
    {
        client.disconnect()->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "Disconnect Error: " << e.what() << '\n';
    }
}

void MQTTClient::subscribe(const std::string& topic){
    try
    {
        client.subscribe(topic, 1)->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "Subscripe Error: " << e.what() << '\n';
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& payload){
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(1);
    try
    {
        client.publish(msg)->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "publish Error: " << e.what() << '\n';
    }
}

// Function to fetch data from MQTT topics
std::vector<std::string> MQTTClient::fetch_sensor_data()
{
    std::vector<std::string> data;

    for (const auto& json_data : data_cache)
    {
        data.push_back(json_data.time_stamp);
    }

    return data;
}

void MQTTClient::message_arrived(mqtt::const_message_ptr msg)
{
    std::string payload = msg->get_payload_str();
    json j = json::parse(payload);
    std::string topic = msg->get_topic();

    if (topic == "sensor_control_data1")
    {
        try
        {
            curr_data.conveyor_upm = j["speed_of_conveyor"].get<int>();
            emit conveyor_speed_changed(curr_data.conveyor_upm);
            if(!curr_data.heater1_manual_control){
                curr_data.heater1 = j["heater_1"].get<bool>();
            }
            if(!curr_data.heater2_manual_control){
                curr_data.heater2 = j["heater_2"].get<bool>();
            }
            if(!curr_data.heater3_manual_control){
                curr_data.heater3 = j["heater_3"].get<bool>();
            }
            emit heater_states(curr_data.heater1, curr_data.heater2, curr_data.heater3);
            if(!curr_data.cooler_manual_control){
                curr_data.cooler = j["cooler"].get<bool>();
                emit cooler_state(curr_data.cooler);
            }
            curr_data.temps = j["temp_sensors"].get<std::array<float, 10>>();
            emit temps_changed(curr_data.temps); // Trigger the signal to update UI
            curr_data.qc_camera_fails = j["qc_camera_fails"].get<int>();

            curr_data.time_stamp = j["time_stamp"].get<std::string>();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON parsing error: " << e.what() << '\n';
        }

        emit db_updated(curr_data);
    }
}

void MQTTClient::update_analytics_values()
{
    get_average_temperature();
    get_failure_rate();
    get_operating_cost();
}

// Function to calculate the failure rate (percentage of failed units out of the total units) from the fetched data
double MQTTClient::get_failure_rate() const
{
    double total_units{0};
    int num_data_points{0}; // Count of the data points for time averaging
    double failed_units{0};

    for (const auto& data : data_cache)
    {
        total_units += data.conveyor_upm * 60;
        failed_units += data.qc_camera_fails;
    }

    double rejectionRate = 0.0;
    if (total_units > 0.0)
    {
        rejectionRate = (failed_units / total_units) * 100.0;
    }
    else
    {
        rejectionRate = 0;
    }

    return rejectionRate;
}

// Function to calculate the operating costs from the fetched data
std::pair<double, double>MQTTClient::get_operating_cost() const
{
    double cost_per_unit{0.5}; // <= can be changed
    // Cost for every heater turned on / unit time
    double heater_cost{3}; // <= can be changed
    // Const for cooler turned on / unit time
    double cooler_cost{5}; // <= can be changed

    double total_units{0};
    double total_cost{0};

    for (const auto& data : data_cache)
    {
        total_units += data.conveyor_upm * 60; // total_units = conveyor speed (units/min) / min
        total_cost += data.conveyor_upm * 60 * cost_per_unit;

        if (data.heater1 || data.heater1_manual_control)
        {
            total_cost += heater_cost;
        }

        if (data.heater2 || data.heater2_manual_control)
        {
            total_cost += heater_cost;
        }

        if (data.heater3 || data.heater3_manual_control)
        {
            total_cost += heater_cost;
        }

        if (data.cooler || data.cooler_manual_control)
        {
            total_cost += cooler_cost;
        }
    }

    double cost_per_unit_time = total_cost / total_units;

    return std::make_pair(total_cost, cost_per_unit_time);
}

// Function to calculate the average temperature of the fetched data
double MQTTClient::get_average_temperature() const
{
    double total_temperature{0};
    int num_temperatures{0};

    for (const auto& data : data_cache)
    {
        for (const auto& temp : data.temps)
        {
            total_temperature += temp;
            num_temperatures++;
        }
    }

    if (num_temperatures > 0)
    {
        return total_temperature / num_temperatures;
    }
    else
    {
        return 0.0; // Return 0 if no temperature data available
    }
}

int MQTTClient::get_average_upm() const
{
    int total_speed{0};
    int num_of_speeds{0};

    for(const auto& data : data_cache)
    {
        total_speed += data.conveyor_upm;
        ++num_of_speeds;
    }
    if(num_of_speeds > 0)
    {
        return total_speed / num_of_speeds;
    }
    else
    {
        return 0;
    }
}

void MQTTClient::publish_data()
{
    json j;
    j["conveyor_manual_control"] = curr_data.conveyor_manual_control;
    j["heater_1_manual_control"] = curr_data.heater1_manual_control;
    j["heater_2_manual_control"] = curr_data.heater2_manual_control;
    j["heater_3_manual_control"] = curr_data.heater3_manual_control;
    j["cooler_manual_control"] = curr_data.cooler_manual_control;
    j["qc_camera_toggle"] = curr_data.qc_camera_toggle;
    j["speed_of_conveyor"] = conveyor_desired_speed;
    j["heater_1"] = curr_data.heater1;
    j["heater_2"] = curr_data.heater2;
    j["heater_3"] = curr_data.heater3;
    j["cooler"] = curr_data.cooler;

    publish("conveyor_params" , j.dump());
}
