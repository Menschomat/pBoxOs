#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoMqttClient.h>
#include <utils/temp.h>
#include <utils/light.h>
#include <utils/fan.h>
#include <avr/dtostrf.h>

// Define pin numbers and other constants
const int LED_PIN = LED_BUILTIN;
const int LIGHT_PIN = 13;
const int FAN_PIN = 12;
const long HEART_INTERVAL_MS = 4000;
const long SENSOR_INTERVAL_MS = 8000;

// Declare global variables
EthernetClient ethClient;

// Helper function to convert a string to an integer
int str_to_int(const char *str, int fallback)
{
  char *endptr;
  int result = strtol(str, &endptr, 10);
  if (*endptr != '\0')
  {
    // The input string is not a valid integer.
    return fallback;
  }
  return result;
}

// Callback function for incoming MQTT messages
void onMqttMessage(int messageSize)
{
  char msg[messageSize + 1]; // add one for the null terminator
  int index = 0;
  while (mqttClient.available())
  {
    msg[index++] = (char)mqttClient.read();
  }
  msg[index] = '\0'; // add null terminator to end of message

  if (mqttClient.messageTopic() == fan_topic)
  {
    fan_level = str_to_int(msg, fan_level);
  }
  else if (mqttClient.messageTopic() == light_topic)
  {
    light_level = str_to_int(msg, light_level);
  }

  Serial.println("Received message: ");
  Serial.print("  topic: ");
  Serial.println(mqttClient.messageTopic());
  Serial.print("  content: ");
  Serial.println(msg);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Initialize Ethernet and MQTT clients
  connectEthernet();
  connectMqtt();
  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(fan_topic);
  mqttClient.subscribe(light_topic);

  // Initialize sensors and actuators
  initTempSens();
  init_lights();
  init_fans();
}

void loop()
{
  // Control the actuators
  analogWrite(LIGHT_PIN, light_level);
  analogWrite(FAN_PIN, fan_level);

  // Check for MQTT messages and handle them
  mqttClient.poll();

  // Send sensor data at regular intervals
  unsigned long currentMillis = millis();
  static unsigned long lastSensorMillis = 0;
  if (currentMillis - lastSensorMillis >= SENSOR_INTERVAL_MS)
  {
    lastSensorMillis = currentMillis;

    char buffer[10];
    sendMsg(sensors_topic, dtostrf(getTemp(), 5, 2, buffer));
  }

  // Send heartbeat message at regular intervals
  static unsigned long lastHeartMillis = 0;
  if (currentMillis - lastHeartMillis >= HEART_INTERVAL_MS)
  {
    lastHeartMillis = currentMillis;

    connectionCheck();
    // sendMsgHeartbeat();
  }
}
