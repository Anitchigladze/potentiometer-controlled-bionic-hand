# potentiometer-controlled-bionic-hand

ESP32-based bionic hand with potentiometer-controlled servo fingers and wireless communication using ESP-NOW.

## Overview

This project implements a 3D-printed bionic hand controlled by two ESP32 microcontrollers. Finger movements are captured using potentiometers on a master hand and transmitted wirelessly via ESP-NOW to a second ESP32, which controls five servo motors to replicate the motion.

## Features

* Wireless communication using ESP-NOW
* Five independently controlled servo-driven fingers
* Potentiometer-based finger motion tracking
* Signal smoothing for stable and responsive movement
* Modular sender and receiver architecture

## Hardware

* 2 × ESP32 development boards
* 5 × MG90S servo motors
* 5 × Potentiometers
* External power supply
* 3D-printed bionic hand
* 3D-printed master hand

## 3D Model

The mechanical design of the hand was **not created by me**.

I used the following open-source designs:

### Bionic Hand

Source: https://www.viralsciencecreativity.com/post/arduino-flex-sensor-controlled-robot-hand

### Master Hand

Source: https://www.thingiverse.com/thing:2782111

My contribution focused on the electronics, programming, system integration, and wireless control. I also designed and added several small custom components to complete the assembly.

## Project Structure

```text
code/
├── bionic_hand_sender_code.ino
└── bionic_hand_receiver_code.ino

schematics/
└── potentiometers.png

media/
└── bionichand.jpg
```

## How to Use

1. Upload the receiver code to one ESP32.
2. Upload the sender code to another ESP32.
3. Connect the potentiometers and servo motors according to the schematic.
4. Power both ESP32 boards.
5. Move the master hand to control the robotic hand wirelessly.

## Media

Project images and demonstration videos are available in the `media` folder.

## Future Improvements

* EMG-controlled hand
* Brain-computer interface (BCI) integration
* Gesture recognition
* Machine learning-based motion prediction

## License

This project is licensed under the MIT License.
