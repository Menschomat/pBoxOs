
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoMqttClient.h>
#include <utils/temp.h>
#include <utils/light.h>
#include <utils/fan.h>
#include <Regexp.h>
#include <avr/dtostrf.h>
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

// set interval for sending messages (milliseconds)
const long heart_interval = 4000;
const long interval = 8000;
unsigned long previousMillis = 0;
unsigned long heart_previousMillis = 0;

int count = 0;

int fanLevel = 0;

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
void onMqttMessage(int messageSize)
{
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  char msg[messageSize + 1]; // add one for the null terminator
  int index = 0;
  while (mqttClient.available())
  {
    msg[index++] = (char)mqttClient.read();
  }
  msg[index] = '\0'; // add null terminator to end of message

  if (mqttClient.messageTopic() == fan_topic)
  {
    fanLevel = str_to_int(msg, fan_level);
  }
  else if (mqttClient.messageTopic() == light_topic)
  {
    light_level = str_to_int(msg, light_level);
  }
  Serial.println(msg);
  Serial.println();
}

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(LED_BUILTIN, OUTPUT);
  connectEthernet();
  connectMqtt();
  initTempSens();
  init_lights();
  init_fans();
  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(fan_topic);
  mqttClient.subscribe(light_topic);
}

void loop()
{
  analogWrite(13, light_level);
  analogWrite(12, fan_level);
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  unsigned long currentMillis = millis();
  if (currentMillis - heart_previousMillis >= heart_interval)
  {
    heart_previousMillis = currentMillis;
    connectionCheck();
    // sendMsgHeartbeat();
  }
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time a message was sent
    previousMillis = currentMillis;
    // send message, the Print interface can be used to set the message contents
    // if (nextTemp != lastTemp)
    //{
    char buffer[10];
    sendMsg(sensors_topic, dtostrf(getTemp(), 5, 2, buffer));
    //}
  }
  mqttClient.poll();
}
