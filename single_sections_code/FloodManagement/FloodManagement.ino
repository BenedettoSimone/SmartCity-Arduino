/* Water level monitoring */
#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521

//PIN for water pump
const int MOTOR_PIN = 8;

int sensorValue = 0; // sensor value
int waterLevel = 0; // water level

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
               
  sensorValue = analogRead(SIGNAL_PIN); // read the analog value from sensor

  waterLevel = map(sensorValue, SENSOR_MIN, SENSOR_MAX, 0, 4); // we divide the height of the sensor in 4 parts
  Serial.print("Water level: ");
  Serial.println(waterLevel);

  if (waterLevel > 1){
    digitalWrite(MOTOR_PIN, HIGH); // turn the water pump ON
  }else{
    digitalWrite(MOTOR_PIN, LOW); // turn the water pump OFF
  } 
  delay(1000);
}

