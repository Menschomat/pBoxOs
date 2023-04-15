#pragma once
#include <Arduino.h>
#include <stdio.h>
#include <utils/mqtt.h>

char fan_topic[120];
int fan_level = 0;

void init_fans()
{
    strcpy(fan_topic, root_topic);
    strcat(fan_topic, BOX_ID);
    strcat(fan_topic, "/fans/");
    strcat(fan_topic, "fan_01");
    char buffer[10];
    sendMsg(fan_topic, itoa(fan_level, buffer, 10));
}