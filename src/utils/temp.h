#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include <utils/mqtt.h>

#define ONE_WIRE_BUS 13 // Sensor DS18B20 am digitalen Pin 2
String senors_topic = root_topic + String("") + BOX_ID + "/sensors/";
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int sensorCount;
float lastTemp = -1024;

void initTempSens()
{
    Serial.println("BEFORE ONEWIRE_INIT");
    sensors.begin();                      // Starten der Kommunikation mit dem Sensor
    sensorCount = sensors.getDS18Count(); // Lesen der Anzahl der angeschlossenen
    Serial.println(sensorCount);
}

float getTemp()
{
    if (sensorCount > 0)
    {
        sensors.requestTemperatures();
        return sensors.getTempCByIndex(0);
    }
    return lastTemp;
}