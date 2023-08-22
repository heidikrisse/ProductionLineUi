// json_parser.cpp
#include "json_parser.h"

json_data::parsed_json json_data::json_to_vec(json &j_data) {
    parsed_json data;

    data.timestamp = j_data["timestamp"].get<std::string>();
    data.units_per_minute = j_data["conveyor_speed"].get<uint16_t>();
    data.heater1_status = j_data["heater1"].get<bool>();
    data.heater2_status = j_data["heater2"].get<bool>();
    data.heater3_status = j_data["heater3"].get<bool>();
    data.cooler_status = j_data["cooler"].get<bool>();
    data.qc_camera_status = j_data["qc_camera"].get<bool>();

    for (int i = 0; i < 10; ++i) {
        std::string sensor_name = "temp_sensor" + std::to_string(i + 1);
        data.heat_sensors[i] = j_data[sensor_name].get<float>();
    }

    // Returns the parsed data
    return data;
}


