// Arduino Uno R4 WiFi Onboard Speaker Test
// This board requires specific setup for the onboard speaker

void setup() {
  Serial.begin(9600);
  Serial.println("=== Arduino Uno R4 WiFi Speaker Test ===");
  Serial.println("Testing onboard speaker with proper configuration...");

  // Configure pins for Arduino Uno R4 WiFi
  pinMode(13, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Wait for board to stabilize
  delay(1000);
}

void loop() {
  Serial.println("\n--- Test 1: Basic tone on pin 13 ---");
  Serial.println("Playing 440 Hz for 2 seconds...");
  tone(13, 440, 2000);
  delay(2500);

  Serial.println("--- Test 2: Higher frequency on pin 13 ---");
  Serial.println("Playing 2000 Hz for 2 seconds...");
  tone(13, 2000, 2000);
  delay(2500);

  Serial.println("--- Test 3: Manual PWM on pin 13 ---");
  Serial.println("Creating tone manually...");
  // Create a tone manually using PWM-like approach
  for(int i = 0; i < 1000; i++) {
    digitalWrite(13, HIGH);
    delayMicroseconds(500);  // 1000 Hz
    digitalWrite(13, LOW);
    delayMicroseconds(500);
  }
  delay(1000);

  Serial.println("--- Test 4: LED_BUILTIN pin test ---");
  Serial.println("Trying LED_BUILTIN pin...");
  tone(LED_BUILTIN, 440, 2000);
  delay(2500);

  Serial.println("--- Test 5: Pin 8 test (alternative) ---");
  Serial.println("Trying pin 8...");
  tone(8, 440, 2000);
  delay(2500);

  Serial.println("\n=== Test Complete ===");
  Serial.println("If no tones were heard, try these solutions:");
  Serial.println("1. Check if your board has an onboard speaker");
  Serial.println("2. Try connecting an external speaker to pin 13");
  Serial.println("3. Check Arduino IDE board settings");
  Serial.println("\nStarting again in 5 seconds...");
  delay(5000);
}