#pragma once
#include <Arduino.h>
#include <utils/mqtt.h>
String fan_topic =  root_topic + String("") + BOX_ID + "/fans/fan_01";