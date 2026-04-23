/*
 * MP3 Melody Player for Arduino
 *
 * This sketch plays melodies using a buzzer speaker.
 * Since Arduino cannot directly play MP3 files, this creates
 * a simplified melody version that can be played on a buzzer.
 *
 * Hardware Setup:
 * - Buzzer speaker connected to pin 8
 * - Optional: Button on pin 7 to change songs
 *
 * Created for kids_arduino project
 */

// Pin definitions
const int BUZZER_PIN = 8;
const int BUTTON_PIN = 7;  // Optional button to change songs

// Musical note frequencies (in Hz)
const int NOTE_C4 = 262;
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_A4 = 440;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;
const int NOTE_D5 = 587;
const int NOTE_E5 = 659;
const int NOTE_F5 = 698;
const int NOTE_G5 = 784;
const int NOTE_A5 = 880;
const int NOTE_B5 = 988;

// Timing definitions
const int QUARTER_NOTE = 500;  // 500ms = quarter note
const int HALF_NOTE = 1000;    // 1000ms = half note
const int WHOLE_NOTE = 2000;   // 2000ms = whole note
const int EIGHTH_NOTE = 250;   // 250ms = eighth note

// Sample melody (you can replace this with your own)
// Format: {frequency, duration}
int sampleMelody[][2] = {
  {NOTE_C4, QUARTER_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_C5, HALF_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_C4, HALF_NOTE},
  {0, QUARTER_NOTE},  // Rest
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_B4, QUARTER_NOTE},
  {NOTE_D5, QUARTER_NOTE},
  {NOTE_G5, HALF_NOTE},
  {NOTE_D5, QUARTER_NOTE},
  {NOTE_B4, QUARTER_NOTE},
  {NOTE_G4, HALF_NOTE},
  {0, QUARTER_NOTE}   // Rest
};

// Twinkle Twinkle Little Star melody
int twinkleMelody[][2] = {
  {NOTE_C4, QUARTER_NOTE},
  {NOTE_C4, QUARTER_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_A4, QUARTER_NOTE},
  {NOTE_A4, QUARTER_NOTE},
  {NOTE_G4, HALF_NOTE},
  {NOTE_F4, QUARTER_NOTE},
  {NOTE_F4, QUARTER_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_D4, QUARTER_NOTE},
  {NOTE_D4, QUARTER_NOTE},
  {NOTE_C4, HALF_NOTE}
};

// Happy Birthday melody
int birthdayMelody[][2] = {
  {NOTE_C4, EIGHTH_NOTE},
  {NOTE_C4, EIGHTH_NOTE},
  {NOTE_D4, QUARTER_NOTE},
  {NOTE_C4, QUARTER_NOTE},
  {NOTE_F4, QUARTER_NOTE},
  {NOTE_E4, HALF_NOTE},
  {NOTE_C4, EIGHTH_NOTE},
  {NOTE_C4, EIGHTH_NOTE},
  {NOTE_D4, QUARTER_NOTE},
  {NOTE_C4, QUARTER_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_F4, HALF_NOTE}
};

// Variables
int currentSong = 0;
int totalSongs = 3;
bool buttonPressed = false;

void setup() {
  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=== MP3 Melody Player ===");
  Serial.println("Press button on pin 7 to change songs");
  Serial.println("Starting in 3 seconds...");
  delay(3000);
}

void loop() {
  // Check for button press to change songs
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    buttonPressed = true;
    currentSong = (currentSong + 1) % totalSongs;
    Serial.print("Switched to song: ");
    Serial.println(currentSong);
    delay(200); // Debounce
  }

  if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonPressed = false;
  }

  // Play the current song
  playCurrentSong();

  // Wait before playing again
  Serial.println("Song finished. Playing again in 2 seconds...");
  delay(2000);
}

void playCurrentSong() {
  Serial.print("Playing song ");
  Serial.println(currentSong);

  switch (currentSong) {
    case 0:
      playMelody(sampleMelody, sizeof(sampleMelody) / sizeof(sampleMelody[0]));
      break;
    case 1:
      playMelody(twinkleMelody, sizeof(twinkleMelody) / sizeof(twinkleMelody[0]));
      break;
    case 2:
      playMelody(birthdayMelody, sizeof(birthdayMelody) / sizeof(birthdayMelody[0]));
      break;
  }
}

void playMelody(int melody[][2], int length) {
  for (int i = 0; i < length; i++) {
    int frequency = melody[i][0];
    int duration = melody[i][1];

    if (frequency > 0) {
      Serial.print("Playing note: ");
      Serial.print(frequency);
      Serial.print(" Hz for ");
      Serial.print(duration);
      Serial.println(" ms");

      tone(BUZZER_PIN, frequency, duration);
      delay(duration + 50); // Small gap between notes
      noTone(BUZZER_PIN);
    } else {
      // Rest (silence)
      Serial.print("Rest for ");
      Serial.print(duration);
      Serial.println(" ms");
      delay(duration);
    }
  }
}

// Function to play a single note
void playNote(int frequency, int duration) {
  if (frequency > 0) {
    tone(BUZZER_PIN, frequency, duration);
    delay(duration + 50);
    noTone(BUZZER_PIN);
  } else {
    delay(duration);
  }
}
