#include "json_parser.h"

void json_data::json_to_vec(json &j_data, std::vector<parsed_json> &json_data_cache)
{
    parsed_json data;
    j_data["timestamp"] = data.timestamp;
    j_data["units_per_minue"] = data.units_per_minute;
    j_data["heater1"] = data.heater1_status;
    j_data["heater2"] = data.heater2_status;
    j_data["heater3"] = data.heater3_status;
    j_data["camera_status"] = data.qc_camera_status;
    j_data["heat sensors"] = data.heat_sensors;
    json_data_cache.push_back(data);
}
