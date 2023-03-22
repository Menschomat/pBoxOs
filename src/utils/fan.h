#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
String fan_topic = root_topic + String("") + BOX_ID + "/fans/fan_01";
int fan_level = 0;

void init_fans()
{
    sendMsg(fan_topic, String(fan_level));
}