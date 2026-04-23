// External Speaker Test for Arduino Uno R4 WiFi
// Connect an external speaker between pin 13 and GND

void setup() {
  Serial.begin(9600);
  Serial.println("=== External Speaker Test ===");
  Serial.println("Connect speaker: Pin 13 -> Speaker -> GND");
  Serial.println("Starting test in 3 seconds...");
  delay(3000);
}

void loop() {
  Serial.println("\n--- Playing Musical Scale ---");

  // Play C major scale
  playNote(262, 500);  // C4
  playNote(294, 500);  // D4
  playNote(330, 500);  // E4
  playNote(349, 500);  // F4
  playNote(392, 500);  // G4
  playNote(440, 500);  // A4
  playNote(494, 500);  // B4
  playNote(523, 1000); // C5

  Serial.println("Scale complete. Playing again in 2 seconds...");
  delay(2000);
}

void playNote(int frequency, int duration) {
  Serial.print("Playing ");
  Serial.print(frequency);
  Serial.print(" Hz for ");
  Serial.print(duration);
  Serial.println(" ms");

  tone(13, frequency, duration);
  delay(duration + 100);  // Wait a bit longer than the tone
  noTone(13);
}