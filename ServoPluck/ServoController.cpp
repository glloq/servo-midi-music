#include "ServoController.h"
#include "settings.h"

ServoController::ServoController() {
  // Initialisation des variables membres
  isUnpowered = true;
  TimeToUnpower = 0;

  // Configuration du pin OE pour contrôler l'alimentation des servos
  pinMode(OE_PIN, OUTPUT);
  digitalWrite(OE_PIN, HIGH); // Désactiver les servos au démarrage

  // Initialisation du tableau de positions
  for (int i = 0; i < NUM_SERVOS; i++) {
    currentPositions[i] = false;
  }

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
  // Validation du numéro de servo
  if (servoNum >= NUM_SERVOS) {
    return;
  }

  // Retour à la position de mute (position initiale)
  setServoAngle(servoNum, initialAngles[servoNum]);
}

// Gratte la corde
void ServoController::pluck(uint8_t servoNum) {
  // Validation du numéro de servo
  if (servoNum >= NUM_SERVOS) {
    return;
  }

  // Actionne le servomoteur pour gratter la corde en fonction du dernier mouvement (position du pick)
  if (currentPositions[servoNum] == 1) {
    setServoAngle(servoNum, initialAngles[servoNum] - PLUCK_ANGLE); // Pick contre la corde à -20°
    currentPositions[servoNum] = 0;
  } else {
    setServoAngle(servoNum, initialAngles[servoNum] + PLUCK_ANGLE); // Pick contre la corde à +20°
    currentPositions[servoNum] = 1;
  }
}