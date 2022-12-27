/* Street lights program. */

const int LED_PIN_1 = 12;
const int LED_PIN_2 = 8;

void setup() {

  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  
  // reads the input on analog pin A3 (value between 0 and 1023)
  int analogValue = analogRead(A3);

  Serial.print("Analog reading: ");
  Serial.print(analogValue);   // the raw analog reading

  /*
  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 10) {
    Serial.println(" - Dark");
  } else if (analogValue < 200) {
    Serial.println(" - Dim");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  */

  if (analogValue < 200){
    // Dark
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
  } else {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
  }
  
  delay(1000);
}