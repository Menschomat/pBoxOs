#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
#include <stdio.h>

// Define a string to hold the topic for the light
char light_topic[120];

// Initialize the light level to zero
int light_level = 0;

// Function to initialize the lights
void init_lights()
{
    // Create the MQTT topic string for the light
    // in the format "test/box_02/lights/led_01"
    strcpy(light_topic, root_topic);
    strcat(light_topic, BOX_ID);
    strcat(light_topic, "/lights/");
    strcat(light_topic, "led_01");

    // Convert the light level integer to a string and
    // send a message to the MQTT broker with the topic
    // and initial light level
    char buffer[10];
    sendMsg(light_topic, itoa(light_level, buffer, 10));
}
