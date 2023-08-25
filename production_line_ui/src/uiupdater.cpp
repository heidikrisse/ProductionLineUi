#include "uiupdater.h"
#include "../include/mqtt_client.h"
uiUpdater::uiUpdater(MQTTClient *client, QObject *parent) : QObject(parent), client(client){

}

void uiUpdater::start()
{
    connect(client, &MQTTClient::mqtt_message_received, this, &uiUpdater::on_MQTT_message_received);
}

void uiUpdater::on_MQTT_message_received(const json& j, const std::string& topic)
{
    if(topic == "conveyer_params")
    {
        try {
            int conveyer_upm = j["conveyer_speed"].get<int>();
            bool conveyer_manual_control = j["conveyer_manual_control"].get<bool>();
            bool heater1_manual_control = j["heater1_manual_control"].get<bool>();
            bool heater2_manual_control = j["heater2_manual_control"].get<bool>();
            bool heater3_manual_control = j["heater3_manual_control"].get<bool>();
            bool cooler_manual_control = j["cooler_manual_control"].get<bool>();
            bool qc_camera_toggle = j["qc_camera_toggle"].get<bool>();
            bool heater1 = j["heater1"].get<bool>();
            bool heater2 = j["heater2"].get<bool>();
            bool heater3 = j["heater3"].get<bool>();
            bool cooler = j["cooler"].get<bool>();
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "json parsing error: " << e.what() << '\n';
        }
    }
}
