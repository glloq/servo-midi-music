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
if (nbrServoActive!=0){// si un servomoteurs est en cours d'utilisation
int timeNow = millis();
  for(int i = 0; i<NUM_SERVOS;i++){
    if (currentlyUsed[i]){// on cherche le servo qui est utilisé
      if (timeReturn[i]<timeNow){// si temps depassé 
        setServoAngle(i, initialAngles[i] );//on remet le servo a sa position initale 
        nbrServoActive--; // et on met a jour le nombre de servo en cours d'utilisation
      }
    }
  }
}

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
  // Utilisé au démarrage pour déplacer les servos en position initiale 
  for (uint8_t i = 0; i < NUM_SERVOS; ++i) {
    setServoAngle(i, initialAngles[i] );
	  delay(100); // délai pour laisser le servos se déplacer
    currentlyUsed[i]=false;
    timeReturn[i]=0;
  }
  nbrServoActive=0;
}

void ServoController::noteOn(uint8_t servoNum) {
  // Actionne le servomoteur dans le bon sens pour l'action noteOn
  if (directionServo[servoNum]){
    setServoAngle(servoNum, initialAngles[servoNum] + PLUCK_ANGLE); 
  }else {
    setServoAngle(servoNum, initialAngles[servoNum] - PLUCK_ANGLE); 
  }
  currentlyUsed[servoNum]=true;
  timeReturn[servoNum]=millis()+TIME_IMPULSION;
  nbrServoActive=nbrServoActive+1;
}