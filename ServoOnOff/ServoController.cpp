#include "ServoController.h"
#include "settings.h"

ServoController::ServoController() {
  // Initialisation des variables membres
  isUnpowered = true;
  TimeToUnpower = 0;

  // Configuration du pin OE pour contrôler l'alimentation des servos
  pinMode(OE_PIN, OUTPUT);
  digitalWrite(OE_PIN, HIGH); // Désactiver les servos au démarrage

  // Calcul du nombre de PCA9685 nécessaires
  int numPcaNeeded = static_cast<int>(ceil(static_cast<double>(NUM_SERVOS) / NUM_SERVOS_PER_PCA));

  if (numPcaNeeded > MAX_NUM_PCA9685) {
    Serial.println("Erreur : Nombre de servo nécessaires dépasse la limite maximale");
    return;
  }

  // Initialisation des PCA9685 avec les adresses I2C définies
  const uint8_t addresses[] = PCA9685_ADDRESSES;
  for (int i = 0; i < numPcaNeeded; i++) {
    pwm[i] = Adafruit_PWMServoDriver(addresses[i]);
    pwm[i].begin();
    pwm[i].setPWMFreq(SERVO_FREQUENCY); // Utilisation de la fréquence correcte (50 Hz)
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
  // Gestion de la coupure d'alimentation des servos (économie d'énergie et réduction du bruit)
  if (!isUnpowered) {
    unsigned long TimeNow = millis();
    // Protection contre le débordement de millis()
    if ((TimeNow - TimeToUnpower) < 0x80000000UL && TimeNow >= TimeToUnpower) {
      digitalWrite(OE_PIN, HIGH); // Désactiver l'alimentation des servos
      isUnpowered = true;
    }
  }
}

void ServoController::setServoAngle(uint8_t servoNum, uint16_t angle) {
  // Validation du numéro de servo
  if (servoNum >= NUM_SERVOS) {
    Serial.print("Erreur : servoNum hors limites : ");
    Serial.println(servoNum);
    return;
  }

  // Vérification que les servos sont alimentés
  checkPowerOn();

  // Calcul de l'index PCA et du canal servo
  int pcaIndex = servoNum / NUM_SERVOS_PER_PCA;
  int servoIndex = servoNum % NUM_SERVOS_PER_PCA;

  // Conversion de l'angle en pulsation PWM
  uint16_t pulsation = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_PULSE_MIN, SERVO_PULSE_MAX);
  pwm[pcaIndex].setPWM(servoIndex, 0, pulsation);
}

void ServoController::resetServosPosition() {
  // Utilisé au démarrage pour déplacer les servos en position initiale 
  for (uint8_t i = 0; i < NUM_SERVOS; ++i) {
    setServoAngle(i, initialAngles[i] );
	  delay(100); // délai pour laisser le servos se déplacer
  }
  
}

void ServoController::noteOff(uint8_t servoNum) {
  // Validation du numéro de servo
  if (servoNum >= NUM_SERVOS) {
    return;
  }

  // Retour à la position initiale
  setServoAngle(servoNum, initialAngles[servoNum]);
}

void ServoController::noteOn(uint8_t servoNum) {
  // Validation du numéro de servo
  if (servoNum >= NUM_SERVOS) {
    return;
  }

  // Actionne le servomoteur dans le bon sens pour l'action noteOn
  if (directionServo[servoNum]) {
    setServoAngle(servoNum, initialAngles[servoNum] + PLUCK_ANGLE);
  } else {
    setServoAngle(servoNum, initialAngles[servoNum] - PLUCK_ANGLE);
  }
}