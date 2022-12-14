# SmartCity-Arduino 🏙

This project treats the development of an IoT smart city using Arduino. The smart city will be equipped with the following functionalities:
- Smart lighting;
- Smart parking lots;
- Air quality monitoring;
- Flood management;
- Waste bucket management;

Each feature will be explained in the dedicated sections.

## Table of contents
* [Getting started](#getting-started-)
  * [1. Host over RaspberryPi 3](#1-host-over-raspberrypi-3)
  * [2. Host on your PC](#2-host-on-your-pc)
* [Materials used in the project](#materials-used-in-the-project-)
* [Step 1: Box creation](#step-1-box-creation)
* [Step 2: Single sections wiring and code](#step-2-single-sections-wiring-and-code)
  * [2.1: Smart lighting](#21-smart-lighting)
  * [2.2: Smart Parking](#22-smart-parking)
  * [2.3: Air quality monitoring](#23-air-quality-monitoring)
  * [2.4: Flood management](#24-flood-management)
  * [2.5: Waste bucket management](#25-waste-bucket-management)
* [Step 3: Create MQTT communication with Web Application](#step-3-create-mqtt-communication-with-web-application)
  * [3.1 Topics and messages format](#31-topics-and-messages-format)
  * [3.2 Publish messages using Arduino](#32-publish-messages-using-arduino)
  * [3.3 Receive messages using a Web Application](#33-receive-messages-using-a-web-application)
* [Step 4: Place all devices on the box model](#step-4-place-all-devices-on-the-box-model) 


## Getting started 🚀
Since our smart sensors can communicate, using MQTT, with a web-application built with Node-Red, we need to setup the enviroment. In our project we used a RaspberryPi 3 to host the MQTT broker and the web-application, but it's possible also to host them on your pc.

## 1. Host over RaspberryPi 3
As first step you need to do the initial setup for the RaspberryPi.
*  Insert a microSD card / reader into your computer.  
*  Download and install the official [Raspberry Pi Imager](https://www.raspberrypi.com/software/). 
*  Run the Imager program, choose the OS as Raspberry Pi OS (32-bit), choose the SD card and write the image. 

### 1.1 - Install MQTT broker
### 1.2 - Install Node-RED

## 2. Host on your PC
### 2.1 - Install MQTT broker
Install the MQTT broker and modify the file ```mosquitto.conf``` inserting the following lines to allow remote access:
```
listener 1885
allow_anonymous true
```
### 2.2 - Install Node-RED
- Download and install [Node.js](https://nodejs.org/en/);
- To ensure the correct installation run in the terminal:
```
node --version && npm –version
```
- Install Node-RED using: 
```
npm install -g --unsafe-perm node-red
```
- Execute:
```
node-red
```
- Now you can access to ``http://localhost:1880`` and you need to install the ``node-red-dashboard`` palette. 

## Materials used in the project 📝
- Box:
  - 4mm thick plywood (1m x 1m);
  - 1.5cm x 1.5cm bar (3.2m);
  - Gray acrylic spray;
  
- Smart Lighting:
  - Light Sensor (Photoresistor);
  - Resistor 10k ohm;
  - Resistor 220 ohm (2x);
  - Yellow LED 5mm (6x);
  - [Street lamp 3D Model](https://www.printables.com/it/model/213148-street-lamp-controlled-by-raspberry-pi-pico) (50% scaled);
  - Solder Iron;
  
- Smart Parking:
  - IR Infrared Obstacle Avoidance Sensor Module (6x);
  - Light Sensor (Photoresistor) (2x);
  - Resistor 10k ohm (2x);
  - KY-008 Laser Module (2x);
  - Servo micro TowerPro sg90 9g;
  - 8x8 Dot Led Matrix Module;

- Air Quality Monitoring:
  - MQ2 Air Quality Sensor;
  
- Flood management:
  - Water Sensor;
 

## Step 1: Box creation
<p align="center"><img src="./images/box_image.jpg"/></p>
Two steps were performed to create the box. For the bottom base (left in photo), a 40cm x 40cm square was cut out and 5cm high sides applied. To make the structure more solid, pieces of the 1.5cm x 1.5cm bar were cut out and applied in the corners. Fastening was done with wood glue and tacks. For the upper base (right in the photo), a 43cm x 43cm square was cut out, applying the sides and the 1.5cm x 1.5cm bar so that it would fit with the bottom base.
Finally, we painted the entire base with gray acrylic spray.

## Step 2: Single sections wiring and code
### 2.1: Smart lighting
<p align="center"><img src="./images/SmartLighting.jpeg"/></p>

The code for this section is available in the folder ``single_sections_code/StreetLights``.


### 2.2: Smart Parking
The various connections for building the smart parking lot have been divided for illustration purposes only. The first image shows the components needed to detect the presence of a car in each lot. The second image shows the components needed for entry and exit in the parking lot equipped with a bar and how available and occupied spaces are shown.

<p align="center"><img src="./images/ParkingWiring.jpg"/></p>
<p align="center"><img src="./images/ParkingEntryExitWiring.jpg"/></p>

The code for this section is available in the folders ``single_sections_code/Parking`` and ``single_sections_code/ParkingBar``.

Library

### 2.3: Air quality monitoring
<p align="center"><img src="./images/AirQuality.jpg"/></p>

The code for this section is available in the folder ``single_sections_code/AirQuality``.


### 2.4: Flood management
<p align="center"><img src="./images/FloodManagement.jpg"/></p>

The code for this section is available in the folder ``single_sections_code/FloodManagement``.


### 2.5: Waste bucket management
The code for this section is available in the folder ``folder``.
Library


## Step 3: Create MQTT communication with Web Application
### 3.1 Topics and messages format
As first step, we estabilished all the topics for the communication:
-  ``topic/street_lights``
-  ``topic/air_quality``
-  ``topic/flood_management``
-  ``topic/parking``

Next, we specified the message format as follows:

```
STREET LIGHTS: 

--- {lights_status: value},

where "value" can be "0" if the lights are OFF, and "1" if they are ON.

```

```
AIR QUALITY MONITORING: 

--- {air_quality_status: value},

where "value" can be "0" if the air quality is GOOD, and "1" if it is BAD.

```

```
FLOOD MANAGEMENT: 

--- {flood_status: value},

where "value" is the water level.

```

```
PARKING: 

--- {free: value, slot1: status, slot2: status, slot3: status, slot4: status, slot5: status, slot6: status},

where "value" is the number of free slots and "status" that can be "0" if the slot is free, "1" if it is busy.

```
### 3.2 Publish messages using Arduino
### 3.3 Receive messages using a Web Application
To built the Web Application to receive and display messages, we used Node Red. The flow is ``flows.json``. The node configuration on Node Red consists of 5 nodes that receive messages from Arduino and are displayed in custom templates. The "template" node named ``custom_template`` was used to customize the style of the dashboard.

<p align="center"><img src="./images/dashboard.jpg"/></p>

## Step 4: Place all devices on the box model




<br><br>
## FINAL RESULT OF EACH SECTION

## Smart lighting
## Smart parking lots
## Air quality monitoring
## Flood management
## Waste bucket management

## Developed with ❤️ by
[Simone Benedetto](https://github.com/BenedettoSimone)<br>
[Salerno Daniele](https://github.com/DanieleSalerno) 
