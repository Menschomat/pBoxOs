#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
#include <stdio.h>

char light_topic[120];
int light_level = 0;

void init_lights()
{
    strcpy(light_topic, root_topic);
    strcat(light_topic, BOX_ID);
    strcat(light_topic, "/lights/");
    strcat(light_topic, "led_01");
    char buffer[10];
    sendMsg(light_topic, itoa(light_level, buffer, 10));
}