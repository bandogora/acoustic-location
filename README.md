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
Connect the microphones to analog in pins starting with analog pin 0, this program supports 4 to *16* microphones.
Connect the output to digital PWM pin one. Optionally, connect the Arduino to the serial monitor.

## Getting started
This program was developed to be used with a grid of a known size. By default the program will
output a 5V PWM signal that represents a location on that grid. If you are using an Arduino and it
detects a serial connection it will also report the array location for the given grid space to the
serial monitor.

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
7. Request a code review*
8. Fix conflicts if necessary

*As of right now pull requests do not require code review.
If you are confident that your code works you can merge the pull request yourself.
Otherwise request a review from one of the other contributers.
