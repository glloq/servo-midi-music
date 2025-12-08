/***********************************************************************************************
----------------------------         SETTINGS               ------------------------------------
************************************************************************************************
Configuration file for the system
Notes are connected in order from the lowest to the highest note, from the first PCA to the last
 Simply provide the first playable MIDI note
 The number of servos used
 If diatonic (8 notes per octave), set DIATONIC_OCTAVE to 1, otherwise 0 (for 12 notes per octave)
 Upload, execute, copy/paste the calibration result for the initial angle of the servos (to get the ideal mute angle with the pick)
************************************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"
#define DEBUG 1

/*--------------------------------------------------------
                  Settings to modify
--------------------------------------------------------*/
#define NUM_SERVOS 16 // Up to 128 servomotors (8 PCAs) for all MIDI notes and 70 notes for diatonic
#define FIRST_MIDI_NOTE 55
#define DIATONIC_OCTAVE 1 // Set to 1 if the instrument uses diatonic tuning, 0 if chromatic
const uint16_t initialAngles[NUM_SERVOS] = {// Copy the calibration result here
  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90
};

const bool directionServo[NUM_SERVOS] = { // Reverse rotation direction if 0
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
#define PLUCK_ANGLE 20 // Movement angle for note On


/*--------------------------------------------------------
          PCA9685 settings
--------------------------------------------------------*/
#define OE_PIN 4 // Arduino output pin for the OE pin
#define TIME_ACTIVE 500 // Time in ms for servo movement before cutting power to servos

// Settings for SG90 servos
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
const uint16_t SERVO_PULSE_MIN = 150;
const uint16_t SERVO_PULSE_MAX = 600;
const uint16_t SERVO_FREQUENCY = 50;

//===============================================================================
//============= Useful stuff for the code

// PCA address management
#define PCA9685_ADDRESSES {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47}  // I2C addresses of PCA9685
#define MAX_NUM_PCA9685 8  // Maximum number of PCA9685 supported
#define NUM_SERVOS_PER_PCA 16 // Maximum number of servos per PCA

/*--------------------------------------------------------
Diatonic instrument management (8 notes per octave)
--------------------------------------------------------*/
const uint8_t MidiDiatonicServoMapping[] = {
    0, 2, 4, 5, 7, 9, 11, // Octave 0
    12, 14, 16, 17, 19, 21, 23, // Octave 1
    24, 26, 28, 29, 31, 33, 35, // Octave 2
    36, 38, 40, 41, 43, 45, 47, // Octave 3
    48, 50, 52, 53, 55, 57, 59, // Octave 4
    60, 62, 64, 65, 67, 69, 71, // Octave 5
    72, 74, 76, 77, 79, 81, 83, // Octave 6
    84, 86, 88, 89, 91, 93, 95, // Octave 7
    96, 98, 100, 101, 103, 105, 107, // Octave 8
    108, 110, 112, 113, 115, 117, 119, // Octave 9
    120, 122, 124, 125, 127 // Octave 10
};





#endif
