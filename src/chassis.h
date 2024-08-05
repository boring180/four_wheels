#ifndef CHASSIS_H
#define CHASSIS_H

#include "motors.h"
#include "pid.h"

class chassis
{
    private:
    public:
    chassis(motor* LF, motor* LB, motor* RF, motor* RB);
    virtual void setSpeedVector(double x, double y, double theta) = 0;
    protected:
    // from range 0.0 ~ 1.0 to -1.0 ~ 1.0 and remove error
    void normSpeedVector(double& x, double& y, double& theta);
    motor* LF;
    motor* LB;
    motor* RF;
    motor* RB;
};

chassis::chassis(motor* LF, motor* LB, motor* RF, motor* RB)
:LF(LF), LB(LB), RF(RF), RB(RB){ }

void chassis::normSpeedVector(double& x, double& y, double& theta)
    {
        x = (x * 2) - 1;
        x = (x > 1.0)? 1.0 : x;
        x = (x < -1.0)? -1.0 : x;
        x = (x < 0.1 && x > -0.1)? 0: x;

        y = (y * 2) - 1;
        y = (y > 1.0)? 1.0 : y;
        y = (y < -1.0)? -1.0 : y;
        y = (y < 0.1 && y > -0.1)? 0: y;

        theta = (theta * 2) - 1;
        theta = (theta > 1.0)? 1.0 : theta;
        theta = (theta < -1.0)? -1.0 : theta;
        theta = (theta < 0.1 && theta > -0.1)? 0: theta;
    }

class arcade: public chassis
{
    public:
    arcade(motor* LF, motor* LB, motor* RF, motor* RB);
    virtual void setSpeedVector(double x, double y, double theta)override;
};

arcade::arcade(motor* LF, motor* LB, motor* RF, motor* RB)
:chassis(LF, LB, RF, RB){ }

void arcade::setSpeedVector(double x, double y, double theta)
{
    normSpeedVector(x, y, theta);
    LF->setSpeed((x + theta) / 2);
    if(LB)
        LB->setSpeed((x + theta) / 2);
    RF->setSpeed((x - theta) / 2);
    if(RB)
        RB->setSpeed((x - theta) / 2);
}

class mechanum: public chassis
{
    public:
    mechanum(motor* LF, motor* LB, motor* RF, motor* RB);
    virtual void setSpeedVector(double x, double y, double theta)override;
};

mechanum::mechanum(motor* LF, motor* LB, motor* RF, motor* RB)
:chassis(LF, LB, RF, RB){ }

void mechanum::setSpeedVector(double x, double y, double theta)
{
    normSpeedVector(x, y, theta);
    RF->setSpeed(y + x + theta);
    LF->setSpeed(y - x - theta);
    RB->setSpeed(y + x + theta);
    LB->setSpeed(y - x - theta);
}

class omni: public chassis
{
    public:
    virtual void setSpeedVector(double x, double y, double theta)override;
    omni(motor* LF, motor* LB, motor* RF, motor* RB);
};

omni::omni(motor* LF, motor* LB, motor* RF, motor* RB)
:chassis(LF, LB, RF, RB)
{

}

void omni::setSpeedVector(double x, double y, double theta)
{
    normSpeedVector(x, y, theta);
    RF->setSpeed(y - x - theta);
    LF->setSpeed(y + x + theta);
    RB->setSpeed(y - x + theta);
    LB->setSpeed(y + x - theta);
}

class headlessOmni: public omni
{
    private:
    double orientation = 0;
    pid* pidControl;
    public:
    void setHeadless(double x, double y, double theta, bool headless = true);
    headlessOmni(motor* LF, motor* LB, motor* RF, motor* RB);
    void setPid(double kp = 1, double ki = 0, double kd = 0);
};

headlessOmni::headlessOmni(motor* LF, motor* LB, motor* RF, motor* RB)
:omni(LF, LB, RF, RB)
{
    pidControl = new pid();
} 

void headlessOmni::setPid(double kp, double ki, double kd)
{
    this->pidControl->setPid(kp, ki, kd);
}

void headlessOmni::setHeadless(double x, double y, double theta, bool headless)
{
    double error;
    pidControl->compute(error)
}

class fixAngleOmni: public chassis
{
    public:
    virtual void setSpeedVector(double x, double y, double theta)override;
};


#endif