# Acoustic Location

A program that runs on an Atmega2560 microcontroller or Arduino and
takes the input from at least four microphones to determine the location
of a noise.

## What's in this repository
- Arduino sketch files
- C code files

## Requirements 
- Minimum 4 omnidirectional microphones
- A way to compile and upload code ([Arduino IDE](https://www.arduino.cc/en/main/software))

## Setup
Clone this repository

#### Arduino
Verify and upload `sketch_n0va`

#### Atmega2560 microcontroller
TBD

#### Hardware
Connect microphones to analog in pins starting with analog pin 0, this program supports 4 to *16* microphones.
Connect output to digital PWM pin one. Optionaly, connect Arduino to serial monitor.

## Getting started
This program was developed to be used with a grid of a known size. By default the the program will
output a 5V PWM signal that represents a location on that grid. If you are using an Arduino and it
detects a serial connection it will also report the array location for the given grid space to the
serial monitor.
