// Super Simple Doll House Buzzer for Kids
// Touch sensor = Jingle Bells song!
// Using Arduino Uno R4 WiFi onboard speaker

int touchPin = 7;    // Touch sensor connects to pin 7
int buzzerPin = 8;   // Buzzer connects to pin 8

// Jingle Bells melody notes (frequencies in Hz) - Improved tuning
int melody[] = {
  523, 523, 523, 523, 523, 523, 523, 392, 523, 659, 330, 392, 330, 262, 330, 392, 440, 415, 392, 330, 523, 659, 784, 659, 523, 392, 330, 262, 330, 523, 523, 523, 523, 523, 523, 523, 392, 523, 659, 330, 392, 330, 262, 330, 392, 440, 415, 392, 330, 523, 659, 784, 659, 523, 392, 330, 262, 330
};

// Note durations (in milliseconds)
int noteDurations[] = {
  200, 200, 400, 200, 200, 400, 200, 200, 200, 400, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 200, 400, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 200, 400
};

void setup() {
  pinMode(touchPin, INPUT);    // Touch sensor is input
  pinMode(buzzerPin, OUTPUT);  // Buzzer is output
}

void loop() {
  // Check if sensor is touched
  if (digitalRead(touchPin) == HIGH) {
    // Play Jingle Bells melody
    playJingleBells();

    // Wait a bit before checking for next touch
    delay(1000);
  }
}

void playJingleBells() {
  // Play each note in the melody
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    // Play the note
    tone(buzzerPin, melody[i], noteDurations[i]);

    // Wait for the note to finish
    delay(noteDurations[i]);

    // Small pause between notes
    delay(50);
  }

  // Turn off buzzer
  noTone(buzzerPin);
}