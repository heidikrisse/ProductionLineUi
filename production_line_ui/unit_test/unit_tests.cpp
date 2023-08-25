// unit_tests.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"

#include "../include/json_parser.h" // for JSON Parser Test
#include "../include/mqtt_client.h" // for MQTT Client Test

/***** JSON PARSER TEST *****/

TEST_CASE("JSON Parser Test")
{
    json_data::parsed_json parsed_data;
    json j;
    j["timestamp"] = "2023-08-22T08:30:00GMT+2";
    j["conveyor_speed"] = 438;
    j["heater1"] = true;
    j["heater2"] = true;
    j["heater3"] = false;
    j["cooler"] = true;
    j["qc_camera"] = true;
    j["temp_sensor1"] = 48.4;
    j["temp_sensor2"] = 53.9;
    j["temp_sensor3"] = 56.2;
    j["temp_sensor4"] = 75.1;
    j["temp_sensor5"] = 79.6;
    j["temp_sensor6"] = 88.2;
    j["temp_sensor7"] = 77.4;
    j["temp_sensor8"] = 62.7;
    j["temp_sensor9"] = 56.3;
    j["temp_sensor10"] = 45.9;

    parsed_data = json_data::json_to_vec(j);

    CHECK(parsed_data.timestamp == "2023-08-22T08:30:00GMT+2");
    CHECK(parsed_data.units_per_minute == 438);
    CHECK(parsed_data.heater1_status == true);
    CHECK(parsed_data.heater2_status == true);
    CHECK(parsed_data.heater3_status == false);
    CHECK(parsed_data.cooler_status == true);
    CHECK(parsed_data.qc_camera_status == true);
    CHECK(parsed_data.heat_sensors[0] == 48.4f);
    CHECK(parsed_data.heat_sensors[1] == 53.9f);
    CHECK(parsed_data.heat_sensors[2] == 56.2f);
    CHECK(parsed_data.heat_sensors[9] == 45.9f);
    CHECK(parsed_data.non_passers == 0);
}

/***** MQTT CLIENT TEST *****/

TEST_CASE("MQTT Client Test")
{
    MQTTClient mqtt_client("broker_address", "client_id");

    SUBCASE("Connect and Disconnect")
    {
        CHECK(mqtt_client.connect() == true);
        mqtt_client.disconnect();
    }

    SUBCASE("Publish and Subscribe")
    {
        CHECK(mqtt_client.connect() == true);
        mqtt_client.subscribe("test/topic");
        mqtt_client.publish("test/topic", "test/payload");
        // Needs a delay / wait for the message to arrive first?
        mqtt_client.disconnect();
    }
}
