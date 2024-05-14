class motor
{
    public:
    motor(char* const name = "Motor");
    virtual void setSpeed(double) = 0;
    void printName()const;
    private:
    char* const name;
};

motor::motor(char* const name):name(name)
{

}

class L298N : public motor
{
    public:
    L298N(int pinA, int pinB, int pinP, char* const name);
    private:
    int pinA;
    int pinB;
    int pinP;
    virtual void setSpeed(double)override;
};

L298N::L298N(int pinA, int pinB, int pinP, char* const name):motor(name), pinA(pinA), pinB(pinB), pinP(pinP)
{

}

void L298N::setSpeed(double)
{
    
}