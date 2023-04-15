#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include <utils/mqtt.h>

#define ONE_WIRE_BUS 14 // Set the digital pin where the DS18B20 sensor is connected
char sensors_topic[120];

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int sensorCount;
float lastTemp = -1024;

void initTempSens()
{
    // Create MQTT topic for temperature sensor
    strcpy(sensors_topic, root_topic);
    strcat(sensors_topic, BOX_ID);
    strcat(sensors_topic, "/sensors/");
    strcat(sensors_topic, "temp_01");
    Serial.println("BEFORE ONEWIRE_INIT");
    
    // Initialize communication with the temperature sensor
    sensors.begin();
    sensorCount = sensors.getDS18Count();
    Serial.println(sensorCount);
}

float getTemp()
{
    // Check if the temperature sensor is connected
    if (sensorCount > 0)
    {
        // Request temperature reading from the sensor
        sensors.requestTemperatures();
        return sensors.getTempCByIndex(0);
    }
    return lastTemp;
}
