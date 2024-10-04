/***********************************************************************************************
----------------------------         SETTINGS               ------------------------------------
************************************************************************************************
fichiers pour la configuration du systeme 
les notes sont branché dans l'ordre de la plus petite note a la plus grande, du premier pca eu dernier
 il suffit de donner la premiere note midi jouable
 le nombre de servo utilisé
 si on est en diatonique (8 notes par octaves) mettre DIATONIC_OCTAVE a 1 sinon 0 (pour 12 notes par octave)
 uploader, executer, copier/coller le resultat de la calibration de l'angle initial des servo (pour avoir l'angle ideal du mute avec le pick)
************************************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"
#define DEBUG 1

/*--------------------------------------------------------
                  reglages a modifier 
--------------------------------------------------------*/
#define NUM_SERVOS 16 // jusqu'a 128 servomoteurs (8pca) pour toutes les notes midi et 70 notes pour le diatonique
#define FIRST_MIDI_NOTE 55
#define DIATONIC_OCTAVE 1 // mettre a 1 si l'instrument utilise un accordage diatonique a 0 si chromatique
const uint16_t initialAngles[NUM_SERVOS] = {//copier le resultat de la calibration ici
  90, 90, 90, 90, 90, 90, 90,
  90, 90, 90, 90, 90, 90, 90,
  90, 90
  };// angle du servo contre la corde 
#define PLUCK_ANGLE 20 //angle de gattage 


/*--------------------------------------------------------
          reglages des PCA9685
--------------------------------------------------------*/
#define OE_PIN 4 // pin de sortie de l'arduino pour la broche OE
#define TIME_ACTIVE 500 // temps en ms pour le deplacement du servomoteur avant de couper l'alimentation des servos

//reglages pour des servo sg90 
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
const uint16_t SERVO_PULSE_MIN = 150;
const uint16_t SERVO_PULSE_MAX = 600;
const uint16_t SERVO_FREQUENCY = 50;

//===============================================================================
//============= stuffs usefull for the code 

//gestion des adresses des pca 
#define PCA9685_ADDRESSES {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47}  // Adresses I2C des PCA9685
#define MAX_NUM_PCA9685 8  // Nombre maximal de PCA9685 supportés
#define NUM_SERVOS_PER_PCA 16 //nombre de servo max par pca

/*--------------------------------------------------------
gestion des instruments diatonique (8 notes par octaves)
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
