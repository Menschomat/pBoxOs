#pragma once
#include <Arduino.h>
#include <utils/mqtt.h> // include the MQTT library
#include <stdio.h>

char fan_topic[120];
int fan_level = 0;

// initialize the fan MQTT topic and level
void init_fans()
{
    // construct the fan MQTT topic by concatenating different strings
    strcpy(fan_topic, root_topic); // root topic is defined somewhere else
    strcat(fan_topic, BOX_ID); // BOX_ID is defined somewhere else
    strcat(fan_topic, "/fans/");
    strcat(fan_topic, "fan_01"); // use "fan_01" as the fan name for now
    
    char buffer[10];
    // convert the integer fan level to a string and send it via MQTT
    sendMsg(fan_topic, itoa(fan_level, buffer, 10));
}
