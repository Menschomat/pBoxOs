#pragma once
#include <Arduino.h>
#include <ArduinoMqttClient.h>

#include <utils/eth.h>

// Set the ID of the box
#define BOX_ID "box_02"

// Set the IP address and port of the MQTT broker
const char broker[] = "10.11.15.21";
int port = 1883;

// Set the root topic for the messages
const char *root_topic = "test/";

// Initialize the MQTT client with the Ethernet client
MqttClient mqttClient(eth_client);

// Function to connect to the MQTT broker
void connectMqtt()
{
    // Set the username and password for the MQTT client
    mqttClient.setUsernamePassword("mqtt_user", "XguoWFgp7rq4Ew34wYid");

    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    // Connect to the MQTT broker
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

// Function to send a message to an MQTT topic
void sendMsg(const char *topic, const char *msg)
{
    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(msg);

    // Begin the message
    mqttClient.beginMessage(topic);
    mqttClient.print(msg);
    mqttClient.endMessage();

    Serial.println("------------------------------------");
}

// Function to send a heartbeat message to the MQTT broker
void sendMsgHeartbeat()
{
    // Set the topic for the heartbeat message
    char topic[120];
    strcpy(topic, root_topic);
    strcat(topic, BOX_ID);
    strcat(topic, "/health");

    // Send the heartbeat message
    sendMsg(topic, "alive");
}

// Function to check the connection to the MQTT broker
void connectionCheck()
{
    if (!mqttClient.connected())
    {
        Serial.println("MQTT connection lost");

        // Reconnect to the MQTT broker
        if (!mqttClient.connect(broker, port))
        {
            Serial.print("MQTT reconnection error ");
            Serial.println(mqttClient.connectError());
        }
    }
}
