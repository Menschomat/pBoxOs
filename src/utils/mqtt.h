#pragma once
#include <Arduino.h>
#include <ArduinoMqttClient.h>

#include <utils/eth.h>
#define BOX_ID "box_02"

const char broker[] = "10.11.15.21";
int port = 1883;

String root_topic = "test/";

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

void sendMsg(String topic, String msg)
{
    String t = topic;
    Serial.print("Sending message to topic: ");
    Serial.println(t);
    Serial.println(msg);
    mqttClient.beginMessage(t);
    mqttClient.print(msg);
    mqttClient.endMessage();
    Serial.println("------------------------------------");
}