#ifndef PID_H
#define PID_H

#include "esp32-hal-ledc.h"

class pid
{   
    private:
    double kp;
    double ki;
    double kd;
    unsigned long previousTime;
    double lastError;
    double cumError;
    public:
    pid(double kp = 1, double ki = 0, double kd = 0);
    double compute(double error);
    void setPid(double kp = 1, double ki = 0, double kd = 0);
};

pid::pid(double kp, double ki, double kd)
: kp(kp), ki(ki), kd(kd)
{

}

double pid::compute(double error)
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - previousTime;
    
    cumError += error * elapsedTime; 
    double rateError = (error - lastError)/elapsedTime;

    double out = kp*error + ki*cumError + kd*rateError;         

    lastError = error;
    previousTime = currentTime;

    return out;              
}

void pid::setPid(double kp, double ki, double kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}


#endif