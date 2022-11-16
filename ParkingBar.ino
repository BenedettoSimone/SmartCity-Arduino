#include <Servo.h>

//inizialize micro servo 9g
Servo servo;

void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //attach the servo to pin 9
  servo.attach(9);
}

void loop() {
  
  // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValueEntry = analogRead(A2);

  //ENABLE THE FOLLOWING CODE TO CHECK THE ISOLATION OF THE LIGHT SENSOR
  /*
  Serial.print("Analog reading entry: ");
  Serial.print(analogValueEntry);   // the raw analog reading

  
  // We'll have a few threshholds, qualitatively determined
  if (analogValueEntry < 10) {
    Serial.println(" - Dark");
  } else if (analogValueEntry < 200) {
    Serial.println(" - Dim");
  } else if (analogValueEntry < 500) {
    Serial.println(" - Light");
  } else if (analogValueEntry < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  */

  
  // reads the input on analog pin A1 (value between 0 and 1023)
  int analogValueExit = analogRead(A1);

   //ENABLE THE FOLLOWING CODE TO CHECK THE ISOLATION OF THE LIGHT SENSOR
  /*
  Serial.print("Analog reading exit: ");
  Serial.print(analogValueExit);   // the raw analog reading

  
  // We'll have a few threshholds, qualitatively determined
  
  if (analogValueExit < 10) {
    Serial.println(" - Dark");
  } else if (analogValueExit < 200) {
    Serial.println(" - Dim");
  } else if (analogValueExit < 500) {
    Serial.println(" - Light");
  } else if (analogValueExit < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  */

  if(analogValueEntry < 800 || analogValueExit < 800){
    Serial.println("Entry or exit: open the bar and leave it open");
    servo.write(90);
  } else{
    Serial.println("Leave the bar closed or close it");
    servo.write(0);
  }

  delay(500);
}


