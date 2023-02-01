#include "LedControl.h"
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Servo.h>


const char* ssid = "WiFi-LabIoT";
const char* password = "s1jzsjkw5b";

const char* mqtt_server = "192.168.1.121";
const int mqtt_port = 1885; //default 1833 

const char *topic_lights = "topic/street_lights";
const char *topic_air = "topic/air_quality";
const char *topic_flood = "topic/flood_management";
const char *topic_parking = "topic/parking";


String parkingMessage = "";
String lightsMessage = "";
String airMessage = "";
String floodMessage = "";

WiFiClient rev2Client; // WiFi client

PubSubClient client(rev2Client); //MQTT client

const int pir1 = 2; // input pin (IR LED parking space 1)
const int pir2 = 3; // input pin (IR LED parking space 2)
const int pir3 = 4; // input pin (IR LED parking space 3)
const int pir4 = 5; // input pin (IR LED parking space 4)
const int pir5 = 6; // input pin (IR LED parking space 5)
const int pir6 = 7; // input pin (IR LED parking space 6)

// output of IR sensors parking
int sensorOut1 = HIGH;  // HIGH = FREE
int sensorOut2 = HIGH;
int sensorOut3 = HIGH;
int sensorOut4 = HIGH;
int sensorOut5 = HIGH;
int sensorOut6 = HIGH;

// number of parking slots available
int freeSlots = 6;
int flag = 0;


Servo servo; //inizialize micro servo 9g

// led matrix
const int numDevices = 1;
LedControl lc = LedControl(11,13,10,numDevices);

// pin to handle street lights
const int LED_PIN_1 = 12;
const int LED_PIN_2 = A4;

//air quality sensor
int airQualitySensor = A0;
int air_value= 0;

//------ flood management
#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521

//PIN for water pump
const int MOTOR_PIN = 8;

int sensorValue = 0; // sensor value
int waterLevel = 0; // water level

void setup() {
  
  Serial.begin(9600);
  
  //attach each parking sensor to pins
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
  pinMode(pir5, INPUT);
  pinMode(pir6, INPUT);

  //attach the servo to pin 9
  servo.attach(9);

  //configure led matrix
  lc.shutdown (0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  //attach led to pin 8 and 12
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  //configure motor pin
  pinMode(MOTOR_PIN, OUTPUT);


  WiFi.begin(ssid, password);
  
  // Start WiFi connection: 
  Serial.print("\nConnecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print("."); 
  }
  Serial.println(); 
  Serial.println("Connected to the WiFi network."); 
  Serial.print("ARDUINOIP_Address:"); 
  Serial.println(WiFi.localIP());
  
  // MQTT connection:
  Serial.println(); 
  client.setServer(mqtt_server, mqtt_port); 

  if (!client.connected()) {
    reconnect();
  }
  
  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  parking();
  delay(200);
  street_lights();
  delay(200);
  air_quality();
  delay(200);
  flood_management();
  delay(200);
  delay(1000);

}



// function to handle parking
void parking(){
/* PARKING BAR SECTION */

  // reads the input on analog pin A2 (value between 0 and 1023)
  int analogValueEntry = analogRead(A1);

  // reads the input on analog pin A1 (value between 0 and 1023)
  int analogValueExit = analogRead(A2);

  
  if(analogValueEntry < 800 && analogValueExit > 800){
    if(freeSlots > 0){

      Serial.println("Entry: open the bar.");
      servo.write(110);
      
      if(flag == 0){
        flag = 1;
        freeSlots--;
      }
    }
    
  }else if (analogValueEntry > 800 && analogValueExit < 800){
    Serial.println("Exit: open the bar.");
    servo.write(110);
    
    if(flag == 0){
      flag = 1;
      freeSlots++;
    }
   
  }else if (analogValueEntry < 800 && analogValueExit < 800){
    Serial.println("Leave the bar open");
    servo.write(110);
  }else{
    Serial.println("Leave the bar closed or close it");
    servo.write(150);
    flag = 0;
  }
  
  
  /* PARKING SECTION */

  //parking space 1
  sensorOut1 = digitalRead(pir1);
  
  if(sensorOut1==LOW){
    setPlace(1,true);
    Serial.println("Parking space 1 BUSY");
  }
  else{
    setPlace(1,false);
    Serial.println("Parking space 1 FREE");
  }
  
  //parking space 2
  sensorOut2 = digitalRead(pir2);

  if(sensorOut2==LOW){
    setPlace(2,true);
    Serial.println("Parking space 2 BUSY");
  }
  else{
    setPlace(2,false);
    Serial.println("Parking space 2 FREE");
  }

  //parking space 3
  sensorOut3 = digitalRead(pir3);

  if(sensorOut3 == LOW){
    setPlace(3,true);
    Serial.println("Parking space 3 BUSY");
  }
  else{
    setPlace(3,false);
    Serial.println("Parking space 3 FREE");
  }

  //parking space 4
  sensorOut4 = digitalRead(pir4);
  if(sensorOut4 ==LOW){
    setPlace(4,true);
    Serial.println("Parking space 4 BUSY");
  }
  else{
    setPlace(4,false);
    Serial.println("Parking space 4 FREE");
  }

  //parking space 5
  sensorOut5 = digitalRead(pir5);
  if(sensorOut5 == LOW){
    setPlace(5,true);
    Serial.println("Parking space 5 BUSY");
  }
  else{
    setPlace(5,false);
    Serial.println("Parking space 5 FREE");
  }

  //parking space 6
  sensorOut6 = digitalRead(pir6);
  if(sensorOut6 == LOW){
    setPlace(6,true);
    Serial.println("Parking space 6 BUSY");
  }
  else{
    setPlace(6,false);
    Serial.println("Parking space 6 FREE");
  }

  parkingMessage = "{\"free\":"+String(freeSlots)+", \"slot1\":"+String(!sensorOut1)+", \"slot2\":"+String(!sensorOut2)+", \"slot3\":"+String(!sensorOut3)+", \"slot4\":"+String(!sensorOut4)+", \"slot5\":"+String(!sensorOut5)+", \"slot6\":"+String(!sensorOut6)+"}";
  
  Serial.println(freeSlots);
  sendMessage(topic_parking, parkingMessage);
}


//funtion to show on led matrix the status of each parking space
void setPlace(int number, boolean state){
  int row = 0;
  int column = 0;
  
  switch(number){
    case 1 :
      row = 0; column = 5; break;

    case 2 :
      row = 3; column = 5; break;

    case 3 :
      row = 6; column = 5; break;

    case 4 :
      row = 0; column = 0; break;

    case 5 :
      row = 3; column = 0; break;

    case 6 :
      row = 6; column = 0; break;
  
  }
  
  lc.setLed(0,row,column,state);
  lc.setLed(0,row,column+1,state);
  lc.setLed(0,row,column+2,state);

  lc.setLed(0,row+1,column,state);
  lc.setLed(0,row+1,column+1,state);
  lc.setLed(0,row+1,column+2,state);
}

//function to handle street lights
void street_lights(){

  /* STREET LIGHTS SECTION */

  // reads the input on analog pin A3 (value between 0 and 1023)
  int analogValueLights = analogRead(A3);

  Serial.print("Analog reading lights: ");
  Serial.println(analogValueLights);   // the raw analog reading

  if (analogValueLights < 200){
    // Dark
    digitalWrite(LED_PIN_1, HIGH);
    analogWrite(LED_PIN_2, 255);
    
    lightsMessage = "{\"lights_status\": 1}";
  } else {
    digitalWrite(LED_PIN_1, LOW);
    analogWrite(LED_PIN_2, 0);
    
    lightsMessage = "{\"lights_status\": 0}";
  }

  sendMessage(topic_lights, lightsMessage);
}


// function to handle air quality
void air_quality(){
  /* AIR QUALITY SECTION */

  air_value = analogRead(airQualitySensor);
  Serial.print("\nAir Quality: ");
  Serial.println(air_value, DEC);

   
  if(air_value > 270){
    //BAD
    airMessage = "{\"air_quality_status\": 1}";
  }else{
    //GOOD    
    airMessage = "{\"air_quality_status\": 0}";
  }

  sendMessage(topic_air, airMessage);
}

void flood_management(){
  /* FLOOD MANAGEMENT SECTION */

  sensorValue = analogRead(SIGNAL_PIN); // read the analog value from sensor

  waterLevel = map(sensorValue, SENSOR_MIN, SENSOR_MAX, 0, 4); // we divide the height of the sensor in 4 parts
  Serial.print("Water level: ");
  Serial.println(waterLevel);

  floodMessage = "{\"flood_status\":"+String(waterLevel)+"}";

  sendMessage(topic_flood, floodMessage);

  if (waterLevel > 1){
    digitalWrite(MOTOR_PIN, HIGH); // turn the water pump ON
  }else{
    digitalWrite(MOTOR_PIN, LOW); // turn the water pump OFF
  } 

}

// publish message
void sendMessage(char *topic_m, String str){
    int str_len = str.length() + 1;
    char char_array[str_len]; 
    str.toCharArray(char_array, str_len); 
    boolean rc = client.publish(topic_m ,char_array);
}


void reconnect() {
  // Loop until we're reconnected 
  Serial.print("Attempting MQTT connection..."); 
  while (!client.connected()) {
    Serial.print("...");
    // Attempt to connect
    if (client.connect("REV2")) {
    Serial.println();
    Serial.println("Connected to the mosquitto Broker.");
    } else {
    Serial.print("failed, rc="); 
    Serial.print(client.state()); 
    Serial.println("Try again in 5 seconds."); 
    delay(5000);  
    }
  }  
}
