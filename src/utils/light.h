#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
String light_topic =  root_topic + String("") + BOX_ID + "/lights/led_01";