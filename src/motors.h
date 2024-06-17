#ifndef MOTORS_H
#define MOTORS_H

#include "esp32-hal-ledc.h"
#include "math.h"

#include "constants.h"

class motor
{
    public:
    motor(const char* name = "Motor", bool reverse = false);
    virtual void setSpeed(double) = 0;
    void printName()const;
    void setReverse();
    private:
    const char* name;
    protected:
    bool reverse;
};

motor::motor(const char* name, bool reverse):name(name), reverse(reverse){}

void motor::setReverse()
{
    reverse = !reverse;
}

/*
void motor::printName()
{
    //TODO
}
*/

class L298N : public motor
{
    public:
    L298N(int pinA, int pinB, int pinP, int ledc, const char* name = "L298N", bool reverse = "false");
    virtual void setSpeed(double)override;
    private:
    int pinA;
    int pinB;
    int pinP;
    int ledC;
};

L298N::L298N(int pinA, int pinB, int pinP, int ledc, const char* name, bool reverse)
:motor(name, reverse), pinA(pinA), pinB(pinB), pinP(pinP), ledC(ledc)
{
    ledcSetup(ledc, L298N_PWM_FREQ, L298N_TIMER_RESOLUTION);
    ledcAttachPin(pinP, ledc);
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void L298N::setSpeed(double speed)
{
    ledcWrite(ledC, abs(speed) * pow(2, L298N_TIMER_RESOLUTION));
    if (reverse) speed *= -1;
    if(speed > 0)
    {
        digitalWrite(pinA, 1);
        digitalWrite(pinB, 0);
    }
    else
    {
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 1);
    }
}

#endif