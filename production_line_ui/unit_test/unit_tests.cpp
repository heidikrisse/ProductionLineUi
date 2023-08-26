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
    j["time_stamp"] = "2023-08-25T15:00:37GMT+2";
    j["speed_of_conveyor"] = 438;
    j["heater_1"] = false;
    j["heater_2"] = false;
    j["heater_3"] = true;
    j["cooler"] = false;
    j["qc_camera_status"] = true;
    j["temp_sensors"] = {48.4, 53.9, 56.2, 41.2, 50.9, 52.3, 46.7, 48.1, 47.3, 45.9};


    parsed_data = json_data::json_to_vec(j);

    CHECK(parsed_data.timestamp == "2023-08-25T15:00:37GMT+2");
    CHECK(parsed_data.units_per_minute == 438);
    CHECK(parsed_data.heater1_status == false);
    CHECK(parsed_data.heater2_status == false);
    CHECK(parsed_data.heater3_status == true);
    CHECK(parsed_data.cooler_status == false);
    CHECK(parsed_data.qc_camera_status == true);
    CHECK(parsed_data.heat_sensors[0] == doctest::Approx(48.4));
    CHECK(parsed_data.heat_sensors[1] == doctest::Approx(53.9));
    CHECK(parsed_data.heat_sensors[2] == doctest::Approx(56.2));
    CHECK(parsed_data.heat_sensors[9] == doctest::Approx(45.9));
    CHECK(parsed_data.non_passers == 0);
}

/***** MQTT CLIENT TEST *****/

TEST_CASE("MQTT Client Test")
{
    MQTTClient mqtt_client("5.tcp.eu.ngrok.io:18017", "abcd1234heidip"); // ("broker_address", "client_id");

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
