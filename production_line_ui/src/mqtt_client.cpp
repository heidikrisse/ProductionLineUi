// mqtt_client.cpp
#include "../include/mqtt_client.h"
#include "../include/json_parser.h"

#include <string>

// Add a message callback to mqtt client
MQTTClient::MQTTClient(const std::string& broker_address, const std::string& client_id)
    : client(broker_address, client_id)
{
    // Set a message callback
    client.set_callback(*this);

    // If connection is succesfull, data_cache will remain empty and live real-time data
    // will be added through message_arrived function to data_cache
    // if (connect())
    // {
    //    live_data_available = true; // Set live data availability to true
    // }
    // else
    // {
    //    data_cache = load_sample_data("../json_examples/"); // Load sample data
    // }
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
        live_data_available = true; // Set live data availability to true
        return true;
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "connection error: " << e.what() << '\n';
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
        std::cerr << "disconnect error: " << e.what() << '\n';
    }
}

void MQTTClient::subscribe(const std::string& topic){
    try
    {
        client.subscribe(topic, 1)->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "subscripe Error: " << e.what() << '\n';
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& payload){
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(1);
    //msg->set_retained(true); // Set retained flag true

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
        data.push_back(json_data.timestamp);
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
            curr_data.qc_camera_toggle = j["qc_camera_toggle"].get<bool>();
            emit qc_camera_state(curr_data.qc_camera_toggle);
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

            curr_data.cooler = j["cooler"].get<bool>();
            emit cooler_state(curr_data.cooler);

            curr_data.temps = j["temp_sensors"].get<std::array<float, 10>>();
            emit temps_changed(curr_data.temps); // Trigger the signal to update UI

            curr_data.qc_camera_fails = j["qc_camera_toggle"].get<int>();

            curr_data.time_stamp = j["time_stamp"].get<std::string>();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "JSON parsing error: " << e.what() << '\n';
        }

        // Parse JSON data and push the data to the data_cache
        json_data::parsed_json parsed = json_data::json_to_vec(j);
        data_cache.push_back(parsed);

        emit db_updated(curr_data);
        if(current_mw_tab == 2)
        {
            update_analytics_values();
        }
    }

}
void MQTTClient::update_analytics_values() const
{
    get_average_temperature();
    get_failure_rate();
    get_operating_cost();
}
// Function to calculate the failure rate from the fetched data
double MQTTClient::get_failure_rate() const
{
    double total_units{0};
    double failed_units{0};

    for (const auto& data : data_cache)
    {
        total_units += data.units_per_minute;
        failed_units += data.non_passers;
    }

    std::cout << "total_units: " << total_units << '\n'; // for debugging
    std::cout << "failed_units: " << failed_units << '\n'; // for debugging

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

        std::cout << "total_units: " << total_units << '\n'; // for debugging

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

// Function to calculate the average temperature of the fetched data
double MQTTClient::get_average_temperature() const
{
    double total_temperature{0};
    int num_temperatures{0};

    for (const auto& data : data_cache)
    {
        for (const auto& temp : data.heat_sensors)
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

    // Update curr_data before emitting the signal
    curr_data.conveyor_upm = j["speed_of_conveyor"].get<int>();
    curr_data.conveyor_manual_control = j["conveyor_manual_control"].get<bool>();

    // Emit db_updated signal with the updated curr_data
    emit db_updated(curr_data);
}
