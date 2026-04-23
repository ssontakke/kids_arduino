/*
 * Tap Module Motor Controller - Arduino Power Version
 *
 * This sketch uses a KY-031 tap module to control a small DC motor
 * powered directly from the Arduino board (no external power supply needed).
 * When the tap module detects a tap, it starts the motor for 1 minute and then stops.
 *
 * IMPORTANT: This version is for SMALL motors only (under 200mA current draw)
 * For larger motors, use the relay version with external power supply.
 *
 * Hardware Setup:
 * - KY-031 tap module connected to pin 2 (interrupt pin)
 * - Small DC motor (3-6V, under 200mA) connected to pin 8 via transistor
 * - Optional: LED indicator on pin 13
 *
 * Wiring:
 * KY-031 Tap Module:
 *   - VCC to 5V
 *   - GND to GND
 *   - DO (Digital Output) to pin 2
 *
 * Motor Circuit:
 *   - Arduino Pin 8 → 220Ω resistor → Transistor base
 *   - Transistor collector → Motor positive
 *   - Transistor emitter → GND
 *   - Motor negative → GND
 *
 * Created for kids_arduino project
 */

// Pin definitions
const int TAP_SENSOR_PIN = 2;    // KY-031 tap module
const int MOTOR_PIN = 8;         // Motor control pin (via transistor)
const int LED_PIN = 13;          // Built-in LED for status indication

// Timing constants
const unsigned long MOTOR_RUN_TIME = 60000;  // 1 minute in milliseconds
const unsigned long DEBOUNCE_TIME = 200;     // Debounce time for tap detection

// Variables
volatile bool tapDetected = false;
volatile unsigned long lastTapTime = 0;
bool motorRunning = false;
unsigned long motorStartTime = 0;

void setup() {
  // Initialize pins
  pinMode(TAP_SENSOR_PIN, INPUT_PULLUP);  // Enable internal pull-up resistor
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Initialize motor as OFF
  digitalWrite(MOTOR_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  // Attach interrupt for tap detection
  // FALLING edge means the sensor output goes from HIGH to LOW when tapped
  attachInterrupt(digitalPinToInterrupt(TAP_SENSOR_PIN), tapInterrupt, FALLING);

  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=== Tap Module Motor Controller (Arduino Power) ===");
  Serial.println("WARNING: Use only small motors (under 200mA)");
  Serial.println("Tap the sensor to start the motor for 1 minute");
  Serial.println("Waiting for tap...");
}

void loop() {
  // Check if tap was detected
  if (tapDetected) {
    tapDetected = false;  // Reset flag

    // Start motor if not already running
    if (!motorRunning) {
      startMotor();
    } else {
      Serial.println("Motor is already running!");
    }
  }

  // Check if motor should be stopped
  if (motorRunning) {
    if (millis() - motorStartTime >= MOTOR_RUN_TIME) {
      stopMotor();
    }
  }

  // Update LED status
  digitalWrite(LED_PIN, motorRunning);

  // Small delay to prevent overwhelming the serial output
  delay(100);
}

// Interrupt service routine for tap detection
void tapInterrupt() {
  unsigned long currentTime = millis();

  // Debounce the tap detection
  if (currentTime - lastTapTime > DEBOUNCE_TIME) {
    tapDetected = true;
    lastTapTime = currentTime;
    Serial.println("Tap detected!");
  }
}

// Function to start the motor
void startMotor() {
  motorRunning = true;
  motorStartTime = millis();
  digitalWrite(MOTOR_PIN, HIGH);

  Serial.println("Motor started!");
  Serial.print("Will run for ");
  Serial.print(MOTOR_RUN_TIME / 1000);
  Serial.println(" seconds");
}

// Function to stop the motor
void stopMotor() {
  motorRunning = false;
  digitalWrite(MOTOR_PIN, LOW);

  Serial.println("Motor stopped!");
  Serial.println("Waiting for next tap...");
}

// Function to get remaining time in seconds
int getRemainingTime() {
  if (!motorRunning) {
    return 0;
  }

  unsigned long elapsed = millis() - motorStartTime;
  unsigned long remaining = MOTOR_RUN_TIME - elapsed;

  if (remaining <= 0) {
    return 0;
  }

  return remaining / 1000;  // Convert to seconds
}
