#include <Arduino.h>
#include "robotContainer.h"

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  testMotor = new AT8236Mini();
  return;

  RF = new L298N(27,14,12,0);
  LF = new L298N(25,26,33,1);
  LF->setReverse();
  RB = new L298N(1,22,23,2);
  RB->setReverse();
  LB = new L298N(19,18,5,3);
  LB->setReverse();

  chassis = new mechanum(LF, LB, RF, RB);

  int* RCPin = new int[3];
  RCPin[0] = 2;
  RCPin[1] = 15;
  RCPin[2] = 4;
  remote = new F_08A(3, RCPin, 1000);
  delete RCPin;
}

void loop() {
  // put your main code here, to run repeatedly:

  return;
  double x = remote->readValue(0);
  double theta = remote->readValue(1);
  double y = remote->readValue(2);
  chassis->setSpeedVector(x ,y , theta);
  //LF->setSpeed(speed);
  //RF->setSpeed(speed);
  //LB->setSpeed(speed);
  //RB->setSpeed(speed);
}

// put function definitions here:

