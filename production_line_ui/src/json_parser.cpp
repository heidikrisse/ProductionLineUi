// json_parser.cpp
#include "../include/json_parser.h"

json_data::parsed_json json_data::json_to_vec(json &j_data)
{
    parsed_json data;

    try
    {
        data.timestamp = j_data["time_stamp"].get<std::string>();  // Update to "time_stamp"
        data.units_per_minute = j_data["speed_of_conveyor"].get<uint16_t>();
        data.heater1_status = j_data["heater_1"].get<bool>();
        data.heater2_status = j_data["heater_2"].get<bool>();
        data.heater3_status = j_data["heater_3"].get<bool>();
        data.cooler_status = j_data["cooler"].get<bool>();
        data.qc_camera_status = j_data["qc_camera_status"].get<bool>();

        auto temp_sensors = j_data["temp_sensors"];
        for (int i{0}; i < temp_sensors.size(); ++i)
        {
            data.heat_sensors[i] = temp_sensors[i].get<float>();
        }

        // Check and get "non-passers" from the JSON if it exists
        if(j_data.contains("non-passers"))
        {
            data.non_passers = j_data["non-passers"].get<uint8_t>();
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "JSON parsing error: " << e.what() << '\n';
    }

    // Returns the parsed data
    return data;
}
