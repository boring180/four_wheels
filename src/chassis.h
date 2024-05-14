#include "motors.h"

class chassis
{
    private:
    motor* LF;
    motor* LB;
    motor* RF;
    motor* RB;
    public:
    chassis(motor* LF, motor* LB, motor* RF, motor* RB);
    virtual void setSpeedVector(int x, int y, int theta) = 0;
};

class tank: public chassis
{
    public:
    virtual void setSpeedVector(int x, int y, int theta)override;
};

class mechanum: public chassis
{
    public:
    virtual void setSpeedVector(int x, int y, int theta)override;
};