
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoMqttClient.h>
#include <utils/temp.h>
#include <utils/light.h>
#include <utils/fan.h>
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

void onMqttMessage(int messageSize)
{
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  String msg = String("");
  while (mqttClient.available())
  {
    msg += (char)mqttClient.read();
  }
  if (mqttClient.messageTopic() == fan_topic)
  {
    fanLevel = 0;
  }
  Serial.println(msg);
  Serial.println();
}

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  /*while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
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
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  unsigned long currentMillis = millis();
  if (currentMillis - heart_previousMillis >= heart_interval)
  {
    heart_previousMillis = currentMillis;
    connectionCheck();
    //sendMsgHeartbeat();
  }
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time a message was sent
    previousMillis = currentMillis;
    // send message, the Print interface can be used to set the message contents
    // if (nextTemp != lastTemp)
    //{
    sendMsg(senors_topic + "temp_01", String(getTemp()));
    //}
  }
  mqttClient.poll();
}
