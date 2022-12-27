/* Street lights program. */


#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "192.168.1.145";
const int mqtt_port = 1885; //default 1883 
const char *topic = "topic/street_lights";


WiFiClient rev2Client; // WiFi client

PubSubClient client(rev2Client); //MQTT client

const int LED_PIN_1 = 12;
const int LED_PIN_2 = 8;


String str = "";


void setup() {

  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

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
  
  // reads the input on analog pin A3 (value between 0 and 1023)
  int analogValueLights = analogRead(A3);

  Serial.print("Analog reading lights: ");
  Serial.print(analogValueLights);   // the raw analog reading

  /*
  // We'll have a few threshholds, qualitatively determined
  if (analogValueLights < 10) {
    Serial.println(" - Dark");
  } else if (analogValueLights < 200) {
    Serial.println(" - Dim");
  } else if (analogValueLights < 500) {
    Serial.println(" - Light");
  } else if (analogValueLights < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  */

  if (analogValueLights < 200){
    // Dark
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    
    str = "{\"light_status\": 1}";

  } else {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    
    str = "{\"light_status\": 0}";
  }
   
  sendMessage(str);
  
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