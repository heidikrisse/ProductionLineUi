// json_parser.h
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "json.hpp"

#include <vector>
#include <iostream>
#include <array>
#include <fstream>

/**
 * The idea of this class is to wrap nlohmanns JSON parser
 * to parse incoming MQTT JSON data into structured C++ objects
 *
 */

using json = nlohmann::json;
namespace json_data
{

    struct parsed_json
    {
        std::string timestamp;
        uint16_t units_per_minute;
        bool heater1_status;
        bool heater2_status;
        bool heater3_status;
        bool cooler_status;
        bool qc_camera_status;
        std::array<float, 10> heat_sensors;
        uint8_t non_passers = 0;
    };

    // Returns parsed_json object
    parsed_json json_to_vec(json &j_data);
};

#endif
