#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include "json.hpp"
#include <vector>
#include <iostream>
#include <array>
#include <fstream>
/**
 * The idea of this class is to wrap nlohmanns JSON parser
 * and Paho MQTT library into one class that gets JSON data
 * trough MQTT connection and parses the contents into objects
 *
 */
using json = nlohmann::json;
namespace json_data{

    struct parsed_json{
        std::string_view timestamp;
        uint16_t units_per_minute;
        bool heater1_status;
        bool heater2_status;
        bool heater3_status;
        bool cooler_status;
        bool qc_camera_status;
        std::array<float, 10> heat_sensors;
    };

    struct failed_qc{
        uint8_t failed_qc_units;
    };
    static std::vector<parsed_json> json_data_cache;

    void json_to_vec(json &j_data, std::vector<parsed_json> &json_data_cache);
};

#endif // JSON_PARSER_H
