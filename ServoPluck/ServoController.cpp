#include "ServoController.h"
#include "settings.h"

ServoController::ServoController() {
  int numPcaNeeded = static_cast<int>(ceil(static_cast<double>(NUM_SERVOS) / NUM_SERVOS_PER_PCA));

  if (numPcaNeeded > MAX_NUM_PCA9685) {
    Serial.println("Erreur : Nombre de servo nécessaires dépasse la limite maximale");
    return;
  }

  for (int i = 0; i < numPcaNeeded; i++) {
    pwm[i].begin();
    pwm[i].setPWMFreq(PCA9685_PRESCALE);
  }
  resetServosPosition();
}

void ServoController::checkPowerOn() {
  TimeToUnpower=millis()+TIME_ACTIVE;//on stocke le temps ou on devra desactiver l'alim des servo après le deplacement
  if(isUnpowered){// si la carte est desactivé
      digitalWrite(OE_PIN, LOW);//on active la carte de ctrl des servos
      isUnpowered=false; //on stocke l'etat de la sortie
  }
}
void ServoController::update() {
  if(!isUnpowered){// si la carte est activé
    unsigned long TimeNow = millis();
    if(TimeNow>TimeToUnpower){
      digitalWrite(OE_PIN, HIGH);//on active la carte de ctrl des servos
      isUnpowered=true; //on stocke l'etat de la sortie
    }
  }
}

void ServoController::setServoAngle(uint8_t servoNum, uint16_t angle) {
  checkPowerOn();//viens verifier que les servo sont activé
  int pcaIndex = servoNum / NUM_SERVOS_PER_PCA;
  int servoIndex = servoNum % NUM_SERVOS_PER_PCA;

  uint16_t pulsation = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
  pwm[pcaIndex].setPWM(servoIndex, 0, pulsation);
}

void ServoController::resetServosPosition() {
  // Utilisé au démarrage pour déplacer les servos en position initiale de grattage
  for (uint8_t i = 0; i < NUM_SERVOS; ++i) {
    setServoAngle(i, initialAngles[i] - PLUCK_ANGLE);
	delay(100); // délai pour laisser les servos se déplacer
  }
  // Puis en position initiale pour initialiser les positions du tableau à 0
  for (uint8_t i = 0; i < NUM_SERVOS; ++i) {
    setServoAngle(i, initialAngles[i]);
	delay(100); //  délai pour laisser les servos se déplacer
  currentPositions[i]=0;//initialise le tableau de la position du pick 
  }
}

void ServoController::mute(uint8_t servoNum) {
  setServoAngle(servoNum, initialAngles[servoNum]);
}

//gratte la corde
void ServoController::pluck(uint8_t servoNum) {
  // Actionne le servomoteur pour gratter la corde en fonction du dernier mouvement (position du pick)
  if (currentPositions[servoNum] == 1) {
    setServoAngle(servoNum, initialAngles[servoNum] - PLUCK_ANGLE);  // Pick contre la corde à -20°
	currentPositions[servoNum] = 0;
  } else {
    setServoAngle(servoNum, initialAngles[servoNum] + PLUCK_ANGLE);  // Pick contre la corde à +20°
	currentPositions[servoNum] = 1;
  }
}