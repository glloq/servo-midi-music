#include "Instrument.h"
#include "settings.h"

Instrument::Instrument() : servoController() {
  //si on utilise une octave a 8 notes => on initialise le tableaux de correspondance midi/servo
  if (DIATONIC_OCTAVE){
    int index=-1;
    int maxSize=sizeof(MidiDiatonicServoMapping);
    for (uint8_t i = 0; i < maxSize; i++) {
      if (MidiDiatonicServoMapping[i]==FIRST_MIDI_NOTE){
        index=i;
        }
    }
    if(index==-1){
      Serial.println("wrong FIRST_MIDI_NOTE for diatonic octave");
      while(1){}
    }
    for (uint8_t i = 0; i < NUM_SERVOS; ++i) {
      MidiServoMapping[i] = MidiDiatonicServoMapping[index+i];
    }
  }
}

int Instrument::getServo(uint8_t midiNote) {
//-------------------------------  Chromatique  -------------------------------------------------------------------
  if (DIATONIC_OCTAVE==0){
    if (midiNote > FIRST_MIDI_NOTE  && midiNote < FIRST_MIDI_NOTE+NUM_SERVOS){//il suffit de verifier si c'est dans un interval de notes
      return midiNote-FIRST_MIDI_NOTE;// on renvoit la position du servo 
    }
    else{
      return -1;// on renvoit -1 si la note n'est pas jouable 
    }
  }  
  //-------------------------------  diatonique   -------------------------------------------------------------------
  else{
    // il suffit de verifier si c'est dans un interval de notes
    if (midiNote > FIRST_MIDI_NOTE  && midiNote < FIRST_MIDI_NOTE+NUM_SERVOS){
    // puis de verifier dans le tabeau 
      for (int i=0; i<NUM_SERVOS;i++){
        if (MidiServoMapping[i]==midiNote){
            return i;//si on trouve la note dans le tableau de correspondance on renvoit la position 
        }
      }
      return -1;// on renvoit -1 si la note n'est pas jouable 
    }
  }
}

void Instrument::noteOn(uint8_t midiNote, uint8_t velocity) {
	int servo=getServo(midiNote);
	if (servo!=-1){
		servoController.pluck(servo);
	}
 }


void Instrument::noteOff(uint8_t midiNote) {
int servo=getServo(midiNote);
	if (servo!=-1){
		// Remet le servo à sa position initiale
		servoController.mute(servo);	    
  }
}
