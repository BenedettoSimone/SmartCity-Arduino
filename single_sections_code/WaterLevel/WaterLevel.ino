/* Water level monitoring */

#define POWER_PIN  7
#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521

int sensorValue = 0; // sensor value
int waterLevel = 0; // water level

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                     
  sensorValue = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  waterLevel = map(sensorValue, SENSOR_MIN, SENSOR_MAX, 0, 4); // we divide the height of the sensor in 4 parts
  Serial.print("Water level: ");
  Serial.println(level);

  delay(1000);
}

