# Playing MP3 Files on Arduino with Buzzer Speaker

## Overview

This project provides tools to play MP3 files on Arduino using a buzzer speaker. Since Arduino cannot directly play MP3 files (they're compressed and require significant processing power), we convert them to simple melodies using tones.

## What You Need

### Hardware
- Arduino board (Uno, Nano, etc.)
- Buzzer speaker
- Jumper wires
- Optional: Push button for song selection

### Software
- Arduino IDE
- Python 3 (for MP3 conversion)
- Required Python packages: `librosa`, `numpy`

## Setup Instructions

### 1. Hardware Connection

Connect your buzzer speaker:
- **Positive (+) wire** → Arduino Pin 8
- **Negative (-) wire** → Arduino GND

Optional button connection:
- **Button one side** → Arduino Pin 7
- **Button other side** → Arduino GND

### 2. Install Python Dependencies

```bash
pip install librosa numpy
```

### 3. Convert Your MP3 File

Use the Python converter script to convert your `sample.mp3` to Arduino code:

```bash
python mp3_to_melody_converter.py sample.mp3
```

This will:
- Analyze your MP3 file
- Extract the main melody
- Generate Arduino code (`mp3_melody.ino`)
- Show you a preview of the extracted notes

### 4. Upload to Arduino

1. Open the generated `mp3_melody.ino` file in Arduino IDE
2. Select your Arduino board and port
3. Click "Upload"

## Available Arduino Sketches

### 1. `mp3_melody_player/mp3_melody_player.ino`
A complete melody player with multiple songs:
- Sample melody
- Twinkle Twinkle Little Star
- Happy Birthday
- Use button on pin 7 to cycle through songs

### 2. `mp3_melody.ino` (generated from your MP3)
Custom melody extracted from your `sample.mp3` file

## How It Works

### MP3 Conversion Process
1. **Load MP3**: The Python script loads your MP3 file
2. **Extract Pitch**: Uses librosa to find the dominant pitch at each time
3. **Map to Notes**: Converts frequencies to Arduino-compatible note frequencies
4. **Generate Code**: Creates Arduino code with the melody array

### Arduino Playback
1. **Tone Generation**: Uses Arduino's `tone()` function to generate specific frequencies
2. **Note Timing**: Controls duration of each note
3. **Melody Loop**: Repeats the melody continuously

## Limitations

### What Arduino CAN Do:
- Play simple melodies using tones
- Control note timing and duration
- Play multiple songs with button control
- Generate different musical scales

### What Arduino CANNOT Do:
- Play actual MP3 files directly
- Reproduce complex audio (drums, multiple instruments)
- Play high-quality audio
- Handle compressed audio formats

## Customization Options

### Change Pin Numbers
Edit the `BUZZER_PIN` constant in the Arduino code:
```cpp
const int BUZZER_PIN = 8;  // Change to your preferred pin
```

### Adjust Note Timing
Modify the timing constants:
```cpp
const int QUARTER_NOTE = 500;  // Faster/slower playback
const int HALF_NOTE = 1000;
const int EIGHTH_NOTE = 250;
```

### Add More Songs
Add new melody arrays and update the song selection logic.

## Troubleshooting

### No Sound
- Check buzzer connections (pin 8 to positive, GND to negative)
- Verify buzzer is working with a simple tone test
- Check Arduino power supply

### Poor Melody Quality
- Try different `max_notes` values in the converter
- Use shorter MP3 files (under 30 seconds)
- Choose MP3 files with clear, simple melodies

### Conversion Errors
- Ensure MP3 file is valid and not corrupted
- Check Python dependencies are installed
- Try with a different MP3 file

## Example Usage

1. **Convert your MP3**:
   ```bash
   python mp3_to_melody_converter.py sample.mp3 --max-notes 30
   ```

2. **Upload to Arduino**:
   - Open `mp3_melody.ino` in Arduino IDE
   - Upload to your board

3. **Listen to the melody**:
   - The buzzer will play your converted melody
   - It will repeat every 2 seconds

## Advanced Features

### Multiple Song Player
Use `mp3_melody_player.ino` to play multiple songs:
- Upload the sketch
- Press the button on pin 7 to cycle through songs
- Each song will play and repeat

### Custom Melodies
Create your own melodies by editing the note arrays:
```cpp
int myMelody[][2] = {
  {262, 500},  // C4 for 500ms
  {330, 500},  // E4 for 500ms
  {392, 1000}, // G4 for 1000ms
  {0, 500}     // Rest for 500ms
};
```

## Tips for Better Results

1. **Choose Simple MP3s**: Files with clear, single-instrument melodies work best
2. **Keep it Short**: 10-30 second clips give good results
3. **Test Different Settings**: Try various `max_notes` values
4. **Use Quality Buzzer**: Better buzzers produce clearer tones
5. **Experiment with Timing**: Adjust note durations for better rhythm

## Files in This Project

- `mp3_melody_player/mp3_melody_player.ino` - Multi-song player
- `mp3_to_melody_converter.py` - MP3 to Arduino converter
- `sample.mp3` - Your MP3 file to convert
- `README_MP3_Player.md` - This documentation

Enjoy making music with your Arduino! 🎵
