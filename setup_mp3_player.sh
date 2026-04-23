#!/bin/bash

# MP3 to Arduino Player Setup Script
# This script helps you convert MP3 files to Arduino melodies

echo "=== MP3 to Arduino Player Setup ==="
echo ""

# Check if virtual environment exists
if [ ! -d "mp3_converter_env" ]; then
    echo "Creating Python virtual environment..."
    python3 -m venv mp3_converter_env
fi

# Activate virtual environment and install dependencies
echo "Installing Python dependencies..."
source mp3_converter_env/bin/activate
pip install librosa numpy

echo ""
echo "=== Setup Complete! ==="
echo ""
echo "To convert your MP3 file to Arduino code:"
echo "1. Activate the environment: source mp3_converter_env/bin/activate"
echo "2. Run the converter: python mp3_to_melody_converter.py sample.mp3"
echo "3. Upload the generated mp3_melody.ino to your Arduino"
echo ""
echo "Hardware setup:"
echo "- Connect buzzer positive (+) to Arduino pin 8"
echo "- Connect buzzer negative (-) to Arduino GND"
echo ""
echo "For more options, run: python mp3_to_melody_converter.py --help"
