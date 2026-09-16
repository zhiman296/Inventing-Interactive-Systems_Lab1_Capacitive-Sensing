# Inventing-Interactive-Systems_Lab1_Capacitive-Sensing

[Demo video] https://youtu.be/Mp-apg1_p-k

This project is a simple interactive sound and light system using three capacitive touch sensors connected to an ESP32.
The three sensors are arranged in a row, and the system responds differently to individual touches and swipe gestures.

### How to run it:
Interactions: 
- Single Touch on Each Sensor: Each sensor produces a different sound.
- Right Swipe (sensor 1 -> sensor 2 -> sensor 3): The system detects a right swipe, plays a rising melody, and turns the LED ON.
- Left Swipe (sensor 3 -> sensor 2 -> sensor 1): Detects a left swipe, plays a falling melody, and turns the LED OFF.

Components:
- ESP32
- 3 capacitive touch sensors(conductive tape)
- 1 LED
- 1 100ohm resistor
- 1 buzzer
- Jumper wires
- Breadboard

Pin Connections:
- Touch sensor 1: GPIO 32
- Touch sensor 2: GPIO 33
- Touch sensor 3: GPIO 12
- LED: GPIO 27
- Buzzer: GPIO 25

<br> 
  

==

*Notes: 
AI was used for debugging the buzzer sound design. I used AI to troubleshoot the code and explore different note sequences 
for the left and right swipe gestures. The goal was to create clearly distinguishable rising and falling melodies while 
making the sounds less harsh.*
