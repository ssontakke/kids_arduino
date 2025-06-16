// Super Simple Doll House Buzzer for Kids
// Touch sensor = Buzzer on for 2 seconds!

int touchPin = 7;    // Touch sensor connects to pin 7
int buzzerPin = 8;   // Buzzer connects to pin 8

void setup() {
  pinMode(touchPin, INPUT);    // Touch sensor is input
  pinMode(buzzerPin, OUTPUT);  // Buzzer is output
}

void loop() {
  // Check if sensor is touched
  if (digitalRead(touchPin) == HIGH) {

    digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
    delay(500);                    // Wait 500ms
    digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF

    // Wait a bit before checking for next touch
    delay(500);
  }
}
