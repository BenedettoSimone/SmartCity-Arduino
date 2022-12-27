/* Air quality program. */

#include <WiFiNINA.h>
#include <PubSubClient.h>


const char* ssid = "";
const char* password = "";

const char* mqtt_server = "192.168.1.22";
const int mqtt_port = 1885; //default 1883 
const char *topic = "topic/air_quality";


WiFiClient rev2Client; // WiFi client

PubSubClient client(rev2Client); //MQTT client

String str = "";


int sensor = A0;
int A0_value= 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin (9600);


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
  // put your main code here, to run repeatedly:

  A0_value = analogRead(sensor);
  Serial.print("\nAir Quality: ");
  Serial.print(A0_value, DEC);

  //Low noise 
  if(A0_value >550){
    Serial.print(A0_value);
    str = "{\"air_quality_status\":BAD}";
  }else{
    str = "{\"air_quality_status\":GOOD}";
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
