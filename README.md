# SmartCity-Arduino 🏙

This project treats the development of an IoT smart city using Arduino. The smart city will be equipped with the following functionalities:
- Smart lighting;
- Smart parking lots;
- Air quality monitoring;
- Flood management;
- Waste bucket management;

Each feature will be explained in the dedicated sections.

## Getting started 🚀
### 1. Install MQTT broker
Install the MQTT broker and modify the file ```mosquitto.conf``` inserting the following lines to allow remote access:
```
listener 1885
allow_anonymous true
```
### 2. Install Node-RED
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
 
 

<br><br>
## STEPS
## Step 1: Box creation
<p align="center"><img src="./images/box_image.jpg"/></p>
Two steps were performed to create the box. For the bottom base (left in photo), a 40cm x 40cm square was cut out and 5cm high sides applied. To make the structure more solid, pieces of the 1.5cm x 1.5cm bar were cut out and applied in the corners. Fastening was done with wood glue and tacks. For the upper base (right in the photo), a 43cm x 43cm square was cut out, applying the sides and the 1.5cm x 1.5cm bar so that it would fit with the bottom base.
Finally, we painted the entire base with gray acrylic spray.

## Step 2: Single sections wiring and code
### 2.1: Smart lighting
<p align="center"><img src="./images/SmartLighting.jpeg"/></p>

The code for this section is available in the folder ``folder``.


### 2.2: Smart Parking
The various connections for building the smart parking lot have been divided for illustration purposes only. The first image shows the components needed to detect the presence of a car in each lot. The second image shows the components needed for entry and exit in the parking lot equipped with a bar and how available and occupied spaces are shown.

<p align="center"><img src="./images/ParkingWiring.jpg"/></p>
<p align="center"><img src="./images/ParkingEntryExitWiring.jpg"/></p>

The code for this section is available in the folder ``folder``.

Library

### 2.3: Air quality monitoring
<p align="center"><img src="./images/AirQuality.jpg"/></p>

The code for this section is available in the folder ``folder``.


### 2.4: Flood management
The code for this section is available in the folder ``folder``.
Library

### 2.5: Waste bucket management
The code for this section is available in the folder ``folder``.
Library


## Step 3: Create MQTT communication with Web Application





## Step 4: Place all devices on the box model




<br><br>
## FINAL RESULT OF EACH SECTION

## Smart lighting
## Smart parking lots
## Air quality monitoring
## Flood management
## Waste bucket management


TODO LIST
- [ ] Create "single_sections_code" folder and insert all the scripts;
- [ ] Step 3: insert mqtt topic scheme, MQTT code on Arduino, node-red flow;



## Developed with ❤️ by
[Simone Benedetto](https://github.com/BenedettoSimone)<br>
[Salerno Daniele](https://github.com/DanieleSalerno) 
