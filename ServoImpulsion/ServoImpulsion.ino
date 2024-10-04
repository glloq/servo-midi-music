/***********************************************************************************************
----------------------------        SERVO PLUCK MIDI MUSIC   -----------------------------------
************************************************************************************************
Systeme construit pour le controle de servomoteurs de type sg90 avec des cartes pac9685
les systeme recoit les messages midi via le cable usb, midiHandler s'occupe de dechiffrer les messages midi
instrument s'occupe de verifier si il peut jouer les notes recues 
ServoController controle le deplacement des servomoteurs 
tout les parametres doivent etre mis dan settings.h afin de simplifier les adaptations au materiel 
************************************************************************************************/
#include <MIDIUSB.h>
#include "Instrument.h"
#include "MidiHandler.h"

Instrument instrument;
MidiHandler midiHandler(instrument);

void setup() {
  Serial.begin(115200);
}

void loop() {
  midiHandler.readMidi();
  instrument.update();
}
