class motor
{
    private:
    int PWM;
    int PWM_C;
    int Dir_A;
    int Dir_B;
    bool rev;
    public:
    void setUp(int Channel,bool reverse,int PWM_Pin);
    void setSpeed(float speed);
};

void motor::setUp(int Channel,bool reverse,int PWM_Pin)
{
    PWM_C = Channel;
    rev = reverse;
    PWM = PWM_Pin;
}

void motor::setSpeed(float speed)
{   
    if(rev)speed *= -1;
    if(speed > 0)
    {
        digitalWrite(Dir_A,0);
        digitalWrite(Dir_B,1);
    }
    else
    {
        digitalWrite(Dir_A,1);
        digitalWrite(Dir_B,0);
    }
    ledcWrite(PWM_C,speed);
}