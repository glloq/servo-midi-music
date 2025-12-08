#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// ONLY MODIFY THIS VARIABLE FOR THE TOTAL NUMBER OF SERVOS
const int totalServos = 32;  // Maximum 128 (8 PCA9685 at 16 servos each)

const int angleInit = 90;  // Initialization angle for all servomotors used before calibration

// PCA parameters for the servos used
#define MIN_PULSE_WIDTH  150
#define MAX_PULSE_WIDTH  600
#define SERVOMIN  150  // Minimum pulse value
#define SERVOMAX  600  // Maximum pulse value

// Create up to 8 PCA9685 modules
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



const int servosPerPCA = 16;  // Number of servos per PCA9685 module
int angles[128];  // Array of angles for all servos
int currentServo = 0;
bool allInitialized = false;

void setup() {
  Serial.begin(9600);

  // Initialize PCA9685 modules according to the number of servos to use
  for (int i = 0; i < (totalServos + servosPerPCA - 1) / servosPerPCA; i++) {
    pca9685[i].begin();
    pca9685[i].setPWMFreq(60);  // Recommended frequency for servos
  }

  // Initialize servos to 90 degrees
  for (int i = 0; i < totalServos; i++) {
    angles[i] = 90;
    setServoAngle(i, angles[i]);
  }

  Serial.println("Enter an angle for servomotor 0:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int angle = input.toInt();

    if (angle >= 0 && angle <= 180) {
      angles[currentServo] = angle;
      setServoAngle(currentServo, angle);
      Serial.print("Angle of servomotor ");
      Serial.print(currentServo);
      Serial.print(": ");
      Serial.println(angle);
      Serial.println("Enter a new angle or type 'next' to move to the next servomotor.");
    } else if (input == "next") {
      currentServo++;
      if (currentServo < totalServos) {
        Serial.print("Enter an angle for servomotor ");
        Serial.println(currentServo);
      } else {
        Serial.println("All servos have been initialized.");
        allInitialized = true;
      }
    }

    if (allInitialized) {
      Serial.println("Angle array to copy into settings.h:");
      Serial.print("[ ");
      for (int i = 0; i < totalServos; i++) {
        Serial.print(angles[i]);
        if (i < totalServos - 1) {
          Serial.print(", ");  // Add a comma between values
        }
      }
      Serial.println(" ]");
      allInitialized = false;
      currentServo = 0;
      Serial.println("Enter a new angle for servomotor 0 to restart.");
    }
  }
}

void setServoAngle(int servoNum, int angle) {
  int pcaIndex = servoNum / servosPerPCA;
  int servoIndex = servoNum % servosPerPCA;

  // Convert angle to PWM value
  int pulseLength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pca9685[pcaIndex].setPWM(servoIndex, 0, pulseLength);
}
