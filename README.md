# Acoustic Location

A program that runs on an Atmega2560 microcontroller and
takes the input from four microphones to determine the location
of a noise.

## What's in this repository
- Arduino sketch files
- C code files

## Requirements
- External ADCs
- 4 omnidirectional microphones
- A way to compile and upload code ([AVRDUDE](https://www.nongnu.org/avrdude/), [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7), [Arduino IDE](https://www.arduino.cc/en/main/software))

## Setup
1. Clone this repository
2. Compile and upload

#### Hardware
Connect the microphones to your ADCs, connect the ADCs output to pins 9 (ICP3), 35 (ICP4), 36 (ICP5), and 47 (ICP1).
If you are using an Arduino Mega the Atmega pins 35 and 36 correspond to Arduino pins 48 and 49. You will need to gain physical access to the Atmega pins 9 and 47.

## Getting started
This program was developed to be used with a grid of a known size. You will need to adjust the delays to correspond with your distances and pulse width. Additionally you will need to compile your own data of known points for the algorithm used.

## Contributing
1. [Connect to Github with SSH](https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
2. Clone this repository with `git clone git@github.com:jforgue/acoustic-location.git`
3. Create a new branch
    1. `git checkout master`
    2. `git checkout -b some-new-branch-name`
4. Commit desired changes
    1. View changes with `git status`
    2. Track desired changes with `git add directory/or/file`
    3. Commit changes with `git commit -m 'commit message'`
5. Push changes with `git push`
6. Make a pull request
7. Request a code review
8. Fix conflicts if necessary
