#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
String light_topic = root_topic + String("") + BOX_ID + "/lights/led_01";
int light_level = 0;

void init_lights()
{
    sendMsg(light_topic, String(light_level));
}