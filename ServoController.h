#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H
/***********************************************************************************************
----------------------------         SERVO CONTROLLER         ----------------------------------
************************************************************************************************
fichier pour la gestion des servomoteurs 
Adapte automatiquement le nombre de pca et leurs adresse au nombre de servo dans l'orde de la note la plus grave a la plus aigue
-------------------------------------------------------------

************************************************************************************************/
#include <Adafruit_PWMServoDriver.h>
#include "settings.h"

class ServoController {
private:
  Adafruit_PWMServoDriver pwm[MAX_NUM_PCA9685];  // Utilisation d'un tableau pour stocker les objets PCA9685
  int16_t currentPositions[NUM_SERVOS];  // Tableau pour stocker le dernier mouvement
  void setServoAngle(uint8_t servoNum, uint16_t angle);

public:
  ServoController();
  void resetServosPosition();
  void mute(uint8_t servoNum);
  void pluck(uint8_t servoNum);
};

#endif // SERVOCONTROLLER_H
