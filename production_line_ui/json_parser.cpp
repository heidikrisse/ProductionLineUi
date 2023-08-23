// json_parser.cpp
#include "json_parser.h"

json_data::parsed_json json_data::json_to_vec(json &j_data) {
    parsed_json data;

    try
    {
        data.timestamp = j_data["timestamp"].get<std::string>();
        data.units_per_minute = j_data["conveyor_speed"].get<uint16_t>();
        data.heater1_status = j_data.value("heater1", false);
        data.heater2_status = j_data.value("heater2", false);
        data.heater3_status = j_data.value("heater3", false);
        data.cooler_status = j_data.value("cooler", false);
        data.qc_camera_status = j_data.value("qc_camera", false);

        for (int i = 0; i < 10; ++i) {
            std::string sensor_name = "temp_sensor" + std::to_string(i + 1);
            data.heat_sensors[i] = j_data.value(sensor_name, 0.0f);
        }

        // Check and get "non-passers" from the JSON if it exists
       /* if(j_data.contains("non-passers")) {
            data.non_passers = j_data["non-passers"].get<uint8_t>();
        }*/
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "JSON parsing error: " << e.what() << '\n';
    }

    // Returns the parsed data
    return data;
}
