#include <Arduino.h>
#include "robotContainer.h"

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  RB = new L298N(27,14,12,0);
  RF = new L298N(25,26,33,1);
  RF->setReverse();
  LF = new L298N(1,22,23,2);
  LB = new L298N(19,18,5,3);
  LB->setReverse();

  chassis = new omni(LF, LB, RF, RB);

  return;
  int* RCPin = new int[3];
  RCPin[0] = 2;
  RCPin[1] = 15;
  RCPin[2] = 4;
  remote = new F_08A(3, RCPin, 1000);
  delete RCPin;
}

void loop() {
  // put your main code here, to run repeatedly:
  chassis->setSpeedVector(0, 1, 0);
}

// put function definitions here:

