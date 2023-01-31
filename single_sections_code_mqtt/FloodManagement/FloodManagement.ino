/* Water level monitoring */

#include <PubSubClient.h>

#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "192.168.1.145";
const int mqtt_port = 1885; //default 1883 
const char *topic = "topic/flood_management";


WiFiClient rev2Client; // WiFi client

PubSubClient client(rev2Client); //MQTT client

String str = "";

//PIN for water pump
const int MOTOR_PIN = 8;

int sensorValue = 0; // sensor value
int waterLevel = 0; // water level

void setup() {
  Serial.begin(9600);
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
               
  sensorValue = analogRead(SIGNAL_PIN); // read the analog value from sensor

  waterLevel = map(sensorValue, SENSOR_MIN, SENSOR_MAX, 0, 4); // we divide the height of the sensor in 4 parts
  Serial.print("Water level: ");
  Serial.println(waterLevel);

  str = "{\"flood_status\":"+String(waterLevel)+"}";

  sendMessage(str);

  if (waterLevel > 1){

    digitalWrite(MOTOR_PIN, HIGH); // turn the water pump ON
  }else{
    digitalWrite(MOTOR_PIN, LOW); // turn the water pump OFF
  } 
  delay(1000);
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

