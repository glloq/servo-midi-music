#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// MODIFIER CETTE VARIABLE SEULEMENT POUR LE NOMBRE TOTAL DE SERVOS
const int totalServos = 32;  // Maximum 128 (8 PCA9685 à 16 servos chacun)

const int angleInit = 90;  // angle initialisation de tout les servomoteurs utilisé avant calibration 

// Parametrtes des pca pour les servo utilisé 
#define MIN_PULSE_WIDTH  150
#define MAX_PULSE_WIDTH  600
#define SERVOMIN  150  // Valeur minimum du pulse
#define SERVOMAX  600  // Valeur maximum du pulse

// Créez jusqu'à 8 modules PCA9685
Adafruit_PWMServoDriver pca9685[8] = {
  Adafruit_PWMServoDriver(0x40),
  Adafruit_PWMServoDriver(0x41),
  Adafruit_PWMServoDriver(0x42),
  Adafruit_PWMServoDriver(0x43),
  Adafruit_PWMServoDriver(0x44),
  Adafruit_PWMServoDriver(0x45),
  Adafruit_PWMServoDriver(0x46),
  Adafruit_PWMServoDriver(0x47)
};



const int servosPerPCA = 16;  // Nombre de servos par module PCA9685
int angles[128];  // Tableau des angles pour tous les servos
int currentServo = 0;
bool allInitialized = false;

void setup() {
  Serial.begin(9600);

  // Initialisation des PCA9685 selon le nombre de servos à utiliser
  for (int i = 0; i < (totalServos + servosPerPCA - 1) / servosPerPCA; i++) {
    pca9685[i].begin();
    pca9685[i].setPWMFreq(60);  // Fréquence recommandée pour les servos
  }

  // Initialisation des servos à 90 degrés
  for (int i = 0; i < totalServos; i++) {
    angles[i] = 90;
    setServoAngle(i, angles[i]);
  }

  Serial.println("Saisissez un angle pour le servomoteur 0 :");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int angle = input.toInt();

    if (angle >= 0 && angle <= 180) {
      angles[currentServo] = angle;
      setServoAngle(currentServo, angle);
      Serial.print("Angle du servomoteur ");
      Serial.print(currentServo);
      Serial.print(" : ");
      Serial.println(angle);
      Serial.println("Saisissez un nouvel angle ou tapez 'next' pour passer au servomoteur suivant.");
    } else if (input == "next") {
      currentServo++;
      if (currentServo < totalServos) {
        Serial.print("Saisissez un angle pour le servomoteur ");
        Serial.println(currentServo);
      } else {
        Serial.println("Tous les servos ont été initialisés.");
        allInitialized = true;
      }
    }

    if (allInitialized) {
      Serial.println("Tableau des angles à copier dans settings.h :");
      Serial.print("[ ");
      for (int i = 0; i < totalServos; i++) {
        Serial.print(angles[i]);
        if (i < totalServos - 1) {
          Serial.print(", ");  // Ajouter une virgule entre les valeurs
        }
      }
      Serial.println(" ]");
      allInitialized = false;
      currentServo = 0;
      Serial.println("Saisissez un nouvel angle pour le servomoteur 0 pour recommencer.");
    }
  }
}

void setServoAngle(int servoNum, int angle) {
  int pcaIndex = servoNum / servosPerPCA;
  int servoIndex = servoNum % servosPerPCA;

  // Convertir l'angle en valeur PWM
  int pulseLength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pca9685[pcaIndex].setPWM(servoIndex, 0, pulseLength);
}
