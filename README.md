# pBoxOS2

This project uses a Raspberry Pico microcontroller to control the temperature, fan, and light of a 3D printer enclosure. It utilizes the DS18B20 temperature sensor and can be controlled remotely via MQTT messages.

### Requirements

- Raspberry Pico microcontroller
- DS18B20 temperature sensor
- Ethernet shield (or equivalent)
- 3D printer enclosure with fan and light

### Pinout

| Component   | Pin |
| ----------- | --- |
| Fan         | 12  |
| Light       | 13  |
| Temperature | 14  |

### Installation

1. Clone this repository to your local machine
2. Open the project in PlatformIO
3. Connect the DS18B20 sensor to the Raspberry Pico
4. Connect the Ethernet shield to the Raspberry Pico and your network
5. Upload the project to your Raspberry Pico using PlatformIO
