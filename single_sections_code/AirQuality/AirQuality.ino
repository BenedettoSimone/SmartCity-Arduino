int sensor = A0;
int A0_value= 0;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  Serial.begin (9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  A0_value = analogRead(sensor);
  Serial.print("\nAir Quality: ");
  Serial.print(A0_value, DEC);

  //Low noise 
  if(A0_value >550){
    Serial.print(A0_value);
  }

  delay(1000);

}
