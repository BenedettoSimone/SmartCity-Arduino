#include "LedControl.h"
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "192.168.1.22";
const int mqtt_port = 1885; //default 1833 
const char *topic = "topic/parking";


WiFiClient rev2Client; // WiFi client

PubSubClient client(rev2Client); //MQTT client

String str = "";

const int pir1 = 2; // input pin (IR LED parking space 1)
const int pir2 = 3; // input pin (IR LED parking space 2)
const int pir3 = 4; // input pin (IR LED parking space 3)
const int pir4 = 5; // input pin (IR LED parking space 4)
const int pir5 = 6; // input pin (IR LED parking space 5)
const int pir6 = 7; // input pin (IR LED parking space 6)

// output of IR sensors
int sensorOut1 = HIGH;  // HIGH = FREE
int sensorOut2 = HIGH;
int sensorOut3 = HIGH;
int sensorOut4 = HIGH;
int sensorOut5 = HIGH;
int sensorOut6 = HIGH;

int freeSlots = 6;


Servo servo; //inizialize micro servo 9g

//const int numDevices = 4;
const int numDevices = 1;

unsigned long delaytime = 1000;

LedControl lc = LedControl(11,13,10,numDevices);


void setup() {
  
  Serial.begin(9600);
  
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
  pinMode(pir5, INPUT);
  pinMode(pir6, INPUT);

  //attach the servo to pin 9
  servo.attach(9);

  lc.shutdown (0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

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
  
  //lc.clearDisplay(0);
  
  // reads the input on analog pin A2 (value between 0 and 1023)
  int analogValueEntry = analogRead(A2);

  // reads the input on analog pin A1 (value between 0 and 1023)
  int analogValueExit = analogRead(A1);

  
  
  if(analogValueEntry < 800 && analogValueExit > 800){
    Serial.println("Entry: open the bar.");
    servo.write(110);
    freeSlots--;
  }else if (analogValueEntry > 800 && analogValueExit < 800){
    Serial.println("Exit: open the bar.");
    servo.write(110);
    freeSlots++;
  }else if (analogValueEntry < 800 && analogValueExit < 800){
    Serial.println("Leave the bar open");
    servo.write(110);
  }else{
    Serial.println("Leave the bar closed or close it");
    servo.write(150);
  }


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

  str = "{\"free\":"+String(freeSlots)+", \"slot1\":"+String(sensorOut1)+", \"slot2\":"+String(sensorOut2)+", \"slot3\":"+String(sensorOut3)+", \"slot4\":"+String(sensorOut4)+", \"slot5\":"+String(sensorOut5)+", \"slot6\": "+String(sensorOut6)+"}";

  sendMessage(str);

  delay(500);

}

//funtion to show on led matrix the status of each parking space
void setPlace(int number, boolean state){
  int row = 0;
  int column = 0;
  
  switch(number){
    case 1 :
      row = 6; column = 5; break;

    case 2 :
      row = 3; column = 5; break;

    case 3 :
      row = 0; column = 5; break;

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

// publish message
void sendMessage(String str){
    int str_len = str.length() + 1;
    char char_array[str_len]; 
    str.toCharArray(char_array, str_len); 
    boolean rc = client.publish(topic,char_array);
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
