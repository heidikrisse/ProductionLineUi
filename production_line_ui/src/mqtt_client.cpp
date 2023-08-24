// mqtt_client.cpp
#include "../include/mqtt_client.h"

#include <string>
#include <filesystem>

// Add a message callback to mqtt client
MQTTClient::MQTTClient(const std::string& broker_address, const std::string& client_id)
    : client(broker_address, client_id)
{
    // Set a message callback
    client.set_callback(*this);

    // Load sample data
    data_cache = load_sample_data("../json_examples"); // removed when we get the real realtime data from group 2
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
        client.subscribe(topic, 2)->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "subscripe Error: " << e.what() << '\n';
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& payload){
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(2);
    msg->set_retained(true); // Set retained flag true

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

    if(topic == "conveyer_params")
    {
        std::string message{msg->get_payload()};
        try {
            conveyer_upm = j["conveyer_speed"].get<int>();
            conveyer_manual_control = j["conveyer_manual_control"].get<bool>();
            heater1_manual_control = j["heater1_manual_control"].get<bool>();
            heater2_manual_control = j["heater2_manual_control"].get<bool>();
            heater3_manual_control = j["heater3_manual_control"].get<bool>();
            cooler_manual_control = j["cooler_manual_control"].get<bool>();
            qc_camera_toggle = j["qc_camera_toggle"].get<bool>();
            conveyer_upm = j["conveyer_speed"].get<int>();
            heater1 = j["heater1"].get<bool>();
            heater2 = j["heater2"].get<bool>();
            heater3 = j["heater3"].get<bool>();
            cooler = j["cooler"].get<bool>();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "json parsing error: " << e.what() << '\n';
        }

    }
   // data_cache.push_back(json_data::json_to_vec(j));
}

std::vector<json_data::parsed_json> MQTTClient::load_sample_data(const std::string& folder_path)
{
    std::vector<json_data::parsed_json> samples;

    // Files to load
    std::vector<std::string> file_names = {
        "camera1.json",
        "camera2.json",
        "camera3.json",
        "line1.json",
        "line2.json",
        "line3.json"
    };

    for (const std::string& file_name : file_names)
    {
        std::string filename = folder_path + "/" + file_name;
        std::ifstream file(filename);

        if (file.is_open())
        {
            json j;
            file >> j;
            samples.push_back(json_data::json_to_vec(j));
            file.close();
        }
    }

    return samples;
}

// Function to calculate the failure rate from the fetched data
double MQTTClient::get_failure_rate() const
{
    double total_units{0};
    double failed_units{0};

        for (const auto& data : data_cache)
        {
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
    // Check if directory exists or create it
    std::filesystem::path file_path(filename);
    if(!std::filesystem::exists(file_path.parent_path())){
        std::filesystem::create_directories(file_path.parent_path());
    }

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
void MQTTClient::publish_data()
{
    json j;
    j["conveyer_manual_control"] = conveyer_manual_control;
    j["heater1_manual_control"] = heater1_manual_control;
    j["heater2_manual_control"] = heater2_manual_control;
    j["heater3_manual_control"] = heater3_manual_control;
    j["cooler_manual_control"] = cooler_manual_control;
    j["qc_camera_toggle"] = qc_camera_toggle;
    j["conveyer_speed"] = conveyer_upm;
    j["heater1"] = heater1;
    j["heater2"] = heater2;
    j["heater3"] = heater3;
    j["cooler"] = cooler;
    publish("conveyer_params" , j.dump());
}
