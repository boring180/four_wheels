#include <Arduino.h>
#include "robotContainer.h"

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, INPUT);

  return;
  RB = new L298N(27,14,12,0);
  RF = new L298N(25,26,33,1);
  RF->setReverse();
  LF = new L298N(17,16,4,2);
  LB = new L298N(19,18,5,3);
  LB->setReverse();

  chassis = new omni(LF, LB, RF, RB);

  int* RCPin = new int[3];
  RCPin[0] = 0;
  RCPin[1] = 2;
  RCPin[2] = 15;
  remote = new F_08A(3, RCPin, 1000);
  delete RCPin;
}

void loop() {
  // put your main code here, to run repeatedly:
  long Htime=pulseIn(2,HIGH,1000);
  Serial.print(Htime);
  Serial.print('\n');
  Serial.print('A');
  delay(20);
  return;
  double x = remote->readValue(0);
  double y = remote->readValue(1);
  double theta = remote->readValue(2);
  //chassis->setSpeedVector(x, y, theta);
  Serial.print(x);
  Serial.print(' ');
  Serial.print(y);
  Serial.print(' ');
  Serial.print(theta);
  Serial.print('\n');
  delay(20);
}

// put function definitions here:

