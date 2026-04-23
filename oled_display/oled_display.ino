#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoBLE.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// BLE Service and Characteristic
BLEService displayService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEStringCharacteristic textCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 50);

String displayText = "Hello Swara";
int scrollX = SCREEN_WIDTH;
const int TEXT_SIZE = 1; // Constant text size

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.display();

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }

  // Set up BLE service
  BLE.setLocalName("OLED Display");
  BLE.setAdvertisedService(displayService);
  displayService.addCharacteristic(textCharacteristic);
  BLE.addService(displayService);

  // Set initial value
  textCharacteristic.writeValue("Hello Swara");

  // Start advertising
  BLE.advertise();

  Serial.println(F("OLED Display Ready!"));
  Serial.println(F("Send any text from your iPhone - it will scroll!"));
}

void loop() {
  // Check for USB Serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    processCommand(command, true);
  }

  // Check for BLE commands
  BLE.poll();

  if (textCharacteristic.written()) {
    String command = textCharacteristic.value();
    command.trim();
    processCommand(command, false);
  }

  // Update scrolling display
  updateDisplay();

  delay(50);
}

void processCommand(String command, bool fromUSB) {
  // If it's not a command, treat it as text
  if (!command.startsWith("clear") && !command.startsWith("help")) {
    displayText = command;
    scrollX = SCREEN_WIDTH; // Reset scroll position

    String response = "Text set to: " + displayText;
    if (fromUSB) {
      Serial.println(response);
    } else {
      textCharacteristic.writeValue(response);
    }
  }
  else if (command == "clear") {
    displayText = "";
    String response = "Display cleared";
    if (fromUSB) {
      Serial.println(response);
    } else {
      textCharacteristic.writeValue(response);
    }
  }
  else if (command == "help") {
    String helpText = "Just send any text and it will scroll! Use 'clear' to clear the display.";
    if (fromUSB) {
      Serial.println(helpText);
    } else {
      textCharacteristic.writeValue(helpText);
    }
  }
}

void updateDisplay() {
  display.clearDisplay();

  // Set text properties
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(scrollX, 8);
  display.println(displayText);

  // Move text position
  scrollX -= 2;

  // Reset when text has scrolled off
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(displayText, 0, 0, &x1, &y1, &w, &h);
  if (scrollX < -w) {
    scrollX = SCREEN_WIDTH;
  }

  display.display();
}
