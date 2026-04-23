# Tap Module Motor Controller

This Arduino project uses a KY-031 tap module to control a DC motor. When someone taps the sensor, the motor starts running for exactly 1 minute and then automatically stops.

## Two Versions Available

### Version 1: External Power (Recommended for 12V motors)
- Uses relay module and external 12V power supply
- Can handle any size motor
- More robust and safe

### Version 2: Arduino Power (For small motors only)
- Powers motor directly from Arduino board
- No external power supply needed
- Limited to small motors (under 200mA)

## Hardware Requirements

### For External Power Version:
- Arduino board (Uno, Nano, or similar)
- KY-031 tap/vibration sensor module
- 5V relay module (for controlling 12V motor)
- 12V DC motor
- 12V power supply for the motor
- Breadboard and jumper wires
- Optional: LED for status indication

### For Arduino Power Version:
- Arduino board (Uno, Nano, or similar)
- KY-031 tap/vibration sensor module
- Small DC motor (3-6V, under 200mA)
- Transistor (2N2222A, BC547, or similar NPN)
- 220Ω resistor
- Breadboard and jumper wires

## Wiring Diagrams

### Version 1: External Power (12V Motor)

#### KY-031 Tap Module
```
KY-031 Module    Arduino
VCC        →     5V
GND        →     GND
DO         →     Pin 2 (Interrupt pin)
```

#### Relay Module
```
Relay Module      Arduino
VCC         →     5V
GND         →     GND
IN          →     Pin 8
```

#### 12V Motor Connection
```
12V Power Supply  →  Relay COM terminal
12V Motor (+)     →  Relay NO terminal
12V Motor (-)     →  12V Power Supply (-)
```

### Version 2: Arduino Power (Small Motor)

#### KY-031 Tap Module
```
KY-031 Module    Arduino
VCC        →     5V
GND        →     GND
DO         →     Pin 2 (Interrupt pin)
```

#### Motor Circuit
```
Arduino Pin 8  →  220Ω Resistor  →  Transistor Base
Transistor Collector  →  Motor (+)
Transistor Emitter    →  GND
Motor (-)             →  GND
```

## Pin Configuration

### Version 1: External Power
| Component | Arduino Pin | Purpose |
|-----------|-------------|---------|
| KY-031 Tap Module | Pin 2 | Tap detection (interrupt) |
| Relay Module | Pin 8 | Motor control |
| Built-in LED | Pin 13 | Status indication |

### Version 2: Arduino Power
| Component | Arduino Pin | Purpose |
|-----------|-------------|---------|
| KY-031 Tap Module | Pin 2 | Tap detection (interrupt) |
| Motor (via transistor) | Pin 8 | Motor control |
| Built-in LED | Pin 13 | Status indication |

## Features

- **Tap Detection**: Uses interrupt-based detection for reliable tap sensing
- **Debouncing**: Prevents false triggers from multiple rapid taps
- **Timer Control**: Automatically stops motor after exactly 1 minute
- **Status LED**: Built-in LED shows when motor is running
- **Serial Output**: Debug information via Serial Monitor
- **Safety**: Prevents multiple motor starts while already running

## How It Works

1. **Setup**: The Arduino initializes pins and attaches an interrupt to the tap sensor
2. **Tap Detection**: When the KY-031 detects a tap, it triggers an interrupt
3. **Motor Start**: The interrupt handler starts the motor and begins a 1-minute timer
4. **Motor Control**: The relay switches on, powering the 12V motor
5. **Timer**: The Arduino continuously checks if 1 minute has elapsed
6. **Motor Stop**: After exactly 1 minute, the motor automatically stops
7. **Status**: The built-in LED indicates when the motor is running

## Installation

### Version 1: External Power (12V Motor)
1. Connect the hardware according to the wiring diagram above
2. Upload the `tap_motor_control.ino` sketch to your Arduino
3. Open the Serial Monitor (9600 baud) to see debug information
4. Tap the sensor to test the system

### Version 2: Arduino Power (Small Motor)
1. Connect the hardware according to the wiring diagram above
2. Upload the `tap_motor_control_arduino_power.ino` sketch to your Arduino
3. Open the Serial Monitor (9600 baud) to see debug information
4. Tap the sensor to test the system

**⚠️ Important**: Only use small motors (under 200mA) with the Arduino power version!

## Troubleshooting

### Motor Doesn't Start
- Check 12V power supply connections
- Verify relay module is properly connected
- Ensure tap sensor is firmly mounted
- Check Serial Monitor for error messages

### False Triggers
- Increase `DEBOUNCE_TIME` value in the code
- Ensure tap sensor is not near vibrations
- Check for loose connections

### Motor Runs Too Long/Short
- Verify the `MOTOR_RUN_TIME` constant (60000ms = 1 minute)
- Check if Arduino clock is accurate

### Tap Not Detected
- Verify KY-031 module connections
- Check if interrupt pin is correct for your Arduino board
- Ensure sensor is properly mounted and can detect vibrations

## Code Customization

### Change Motor Run Time
```cpp
const unsigned long MOTOR_RUN_TIME = 30000;  // 30 seconds
```

### Change Debounce Time
```cpp
const unsigned long DEBOUNCE_TIME = 500;     // 500ms debounce
```

### Add Multiple Motors
```cpp
const int MOTOR_RELAY_PIN_2 = 9;  // Second motor
// Add additional relay pins and control logic
```

## Safety Notes

- Always disconnect power before making wiring changes
- Ensure 12V power supply can handle motor current
- Use appropriate wire gauge for motor connections
- Consider adding a fuse for motor protection
- Keep motor and electronics away from water

## Parts List

- Arduino Uno/Nano: $5-10
- KY-031 Tap Module: $2-5
- 5V Relay Module: $3-8
- 12V DC Motor: $5-15
- 12V Power Supply: $10-20
- Breadboard & Wires: $5-10

**Total Cost: ~$30-70**

## Advanced Features

You can extend this project with:
- Multiple tap sensors for different motors
- Variable motor speed control
- LCD display showing countdown timer
- Bluetooth control for remote operation
- Multiple motor sequences
- Sound effects when motor starts/stops
