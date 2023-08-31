// unit_tests.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"

#include "../include/mqtt_client.h" // for MQTT Client Test
#include "../include/sqlite.hpp"

/***** MQTT CLIENT TESTS *****/

// Define a mock class to use for testing
class MockMQTTClient : public MQTTClient
{
public:
    using MQTTClient::MQTTClient;
    using MQTTClient::data_cache;
    using MQTTClient::get_failure_rate;
    using MQTTClient::get_operating_cost;
    using MQTTClient::get_average_temperature;
    using MQTTClient::get_average_upm;
    using MQTTClient::update_analytics_values;
};

TEST_CASE("MQTT Client tests: Connect and Disconnect")
{
    MQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip"); // ("broker_address", "client_id");

    CHECK(mqtt_client.connect() == true);
    mqtt_client.disconnect();
}

TEST_CASE("MQTT Client tests: Publish Data")
{
    MQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");
    mqtt_client.connect();

    CHECK_NOTHROW(mqtt_client.publish_data());
    mqtt_client.disconnect();
}

TEST_CASE("MQTT Client tests: Update Analytics Values")
{
    MQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");

    CHECK_NOTHROW(mqtt_client.update_analytics_values());
}

TEST_CASE("MQTT Client tests: Failure Rate Calculation")
{
    MockMQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");

    // Clear the data cache
    mqtt_client.data_cache.clear();

    // Add some sample data
    CurrentConveyorData data1;
    data1.qc_camera_fails = 10;
    data1.conveyor_upm = 400; // 400 units/min
    mqtt_client.data_cache.push_back(data1);

    double failure_rate{mqtt_client.get_failure_rate()};
    double expected_failure_rate{(10.0 / (400.0 * 60.0)) * 100.0};

    CHECK(failure_rate == doctest::Approx(expected_failure_rate).epsilon(0.001));
}

TEST_CASE("MQTT Client tests: Operating Cost Calculation")
{
    MockMQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");

    // Clear the data cache
    mqtt_client.data_cache.clear();

    // Add some sample data
    CurrentConveyorData data1;
    data1.conveyor_upm = 500; // 500 units/min
    data1.heater1 = true;
    data1.heater2 = false;
    data1.heater3 = true;
    data1.cooler = false;
    mqtt_client.data_cache.push_back(data1);

    std::pair<double, double> operating_cost = mqtt_client.get_operating_cost();
    double expected_total_cost{(500.0 * 60 * 0.36) + (3 + 3 + 5)}; // cost_per_unit * total_units + heater_costs
    double expected_cost_per_unit_time{expected_total_cost / (500.0 * 60)};

    CHECK(operating_cost.first == doctest::Approx(expected_total_cost).epsilon(0.001));
    CHECK(operating_cost.second == doctest::Approx(expected_cost_per_unit_time).epsilon(0.001));
}

TEST_CASE("MQTT Client tests: Average Temperature Calculation")
{
    MQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");

    CurrentConveyorData data1;
    data1.temps = {45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0};
    mqtt_client.data_cache = {data1};

    double average_temp{mqtt_client.get_average_temperature()};

    double expected_average_temp{49.5};

    CHECK(average_temp == doctest::Approx(expected_average_temp).epsilon(0.001));
}

TEST_CASE("MQTT Client tests: Average UPM Calculation")
{
    MQTTClient mqtt_client("test.mosquitto.org:1883", "abcd1234heidip");

    // Sample data for average UPM calculation into the data_cache
    CurrentConveyorData data1;
    data1.conveyor_upm = 400;
    CurrentConveyorData data2;
    data2.conveyor_upm = 398;
    CurrentConveyorData data3;
    data3.conveyor_upm = 401;
    mqtt_client.data_cache = {data1, data2, data3};

    int average_upm{mqtt_client.get_average_upm()};

    int expected_average_upm{399};

    CHECK(average_upm == expected_average_upm);
} 

/***** DATABASE TESTS *****/

TEST_CASE("Database tests: Create DB and Table")
{
    std::unique_ptr<Db_manager> db = std::make_unique<Db_manager>();

    // Returns true if db and table is created
    bool db_and_table_created = db->Db_manager::create_connection();

    CHECK(db_and_table_created == true);
}
