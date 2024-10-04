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
  bool currentlyUsed[NUM_SERVOS];  // Tableau pour stocker le servo activé  
  unsigned long timeReturn[NUM_SERVOS];  // Tableau pour stocker quand il faut remettre le servo en position initiale
  void setServoAngle(uint8_t servoNum, uint16_t angle);
  void checkPowerOn();// viens verifer que la pin OE est a 0 pout faire un mouvment d'un servo
  bool isUnpowered; // stocke l'etat du pin OE 
  unsigned long TimeToUnpower ; //temps quand il faut desactiver les servo
  int nbrServoActive ; // nombre de servo en cours d'utilisation 
  
public:
  ServoController();
  void resetServosPosition();
  void noteOn(uint8_t servoNum);
  void update (); // permet de couper l'alimentation des servomoteur après un mouvment pour reduire le bruit
};

#endif // SERVOCONTROLLER_H
