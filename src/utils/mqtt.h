#pragma once
#include <Arduino.h>
#include <ArduinoMqttClient.h>

#include <utils/eth.h>
#define BOX_ID "box_02"

const char broker[] = "10.11.15.21";
int port = 1883;

const char *root_topic = "test/";

MqttClient mqttClient(eth_client);

void connectMqtt()
{
    mqttClient.setUsernamePassword("mqtt_user", "XguoWFgp7rq4Ew34wYid");
    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    if (!mqttClient.connect(broker, port))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
        while (1)
            ;
    }
    Serial.println("You're connected to the MQTT broker!");
    Serial.println("------------------------------------");
}

void sendMsg(const char *topic, const char *msg)
{
    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(msg);
    mqttClient.beginMessage(topic);
    mqttClient.print(msg);
    mqttClient.endMessage();
    Serial.println("------------------------------------");
}
void sendMsgHeartbeat()
{
    char topic[120];
    strcpy(topic, root_topic);
    strcat(topic, BOX_ID);
    strcat(topic, "/health");
    sendMsg(topic, "alive");
}

void connectionCheck()
{
    if (!mqttClient.connected())
    {
        Serial.println("MQTT connection lost");
        if (!mqttClient.connect(broker, port))
        {
            Serial.print("MQTT reconnection error ");
            Serial.println(mqttClient.connectError());
        }
    }
}