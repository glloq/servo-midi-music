> [!NOTE]
> Project completed but code not tested yet!

# servo-midi-music

The objective is to have code to control servomotors using PCA9685 boards based on MIDI messages received via USB.
All settings will be grouped in the settings.h file (number of servos to use, servo angles, PCA servo control parameters, scale type used, etc.).
Servomotor management is dynamic and can adapt to different numbers of notes thanks to the use of multiple PCA9685 as needed.
The servomotors will be connected starting with the lowest note on pin 0 of the first PCA used, the second note on pin 1 of the PCA and so on.
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/SchemaElec.png" alt="pluck" width=100% height=100%/>
To limit servomotor noise, we will use the OE pin of the PCA to disable power to the servomotors when they are not in use.


# Applications

There are 3 types of actions for noteOn/noteOff messages:
- Plucking => the servo alternates by +/- a certain plucking angle for a noteOn and returns to zero position on a noteOff
- Activation => the servo moves by a certain angle on noteOn and returns to zero position on a noteOff
- Impulse => the servo moves by a certain angle on noteOn and returns to zero position after a certain time

## ServoPluck
This code is built to pluck strings (lyre, harp, etc.) or other plucking systems and will alternate the plucking direction on each noteOn message.
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/grattage.png" alt="pluck" width=40% height=40%/>

Simply adapt the following settings in settings.h:
- The number of servos used (NUM_SERVOS)
- The scale type used (DIATONIC_OCTAVE set to 1 if using diatonic tuning and 0 if chromatic)
- The initialization angles of the servomotors (in the initialAngles[] array)
- The plucking angle of the servomotors (PLUCK_ANGLE)

## ServoOnOff

This code is built to actuate the servomotor in one direction upon receiving a MIDI noteOn message, then returns the servomotor to its initial position upon receiving a noteOff message.
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/OnOff.png" alt="OnOff" width=30% height=30%/>

Simply adapt the following settings in settings.h:
- The number of servos used (NUM_SERVOS)
- The scale type used (DIATONIC_OCTAVE set to 1 if using diatonic tuning and 0 if chromatic)
- The initialization angles of the servomotors (in the initialAngles array)
- The direction for servo action (in the DirectionServo[] array)
- The plucking angle of the servomotors (PLUCK_ANGLE)


## ServoImpulsion

This code is built to actuate the servomotor in one direction upon receiving a MIDI noteOn message, then returns the servomotor to its initial position after a certain time defined in settings.h.
The parameters are the same as in the ServoOnOff code with the impulse time before returning the servo to its initial position (TIME_IMPULSION).


# Servomotor Calibration

To simplify the use of the code, it is possible to use the code in the calibration file to determine the position of each servomotor.
Simply enter the number of servomotors used and then upload the code to the Arduino.


You can modify the position of each servomotor one after another from the serial console of the Arduino IDE. Once all servomotors are initialized, you need to copy and paste the angle array into the settings.h file used. 
