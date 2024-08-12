#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

class receiver
{
    public:
    receiver(const char* name = "RC", int chaneelNum = 4, int* inputPorts = nullptr);
    virtual void printValue() const = 0;
    void printName()const;
    virtual double readValue(int) const = 0;
    virtual bool readSwitch(int) const = 0;
    ~receiver();
    private:
    const char* name;
    protected:
    int channelNum;
    int* ports;
};

receiver::receiver(const char* name, int channelNum, int* inputPorts )
:name(name), channelNum(channelNum)
{
    ports = new int[channelNum];
    for(int i = 0; i < channelNum; i++)
    {
        ports[i] = inputPorts[i];
    }
}

receiver::~receiver()
{
    delete [] ports;
}

/*
void receiver::printName()
{
    //TODO
}
*/

class F_08A : public receiver
{
    public:
    F_08A(int channelNum, int* inputPorts, int timeOut, const char* name = "F_08A");
    double readValue(int) const override;
    bool readSwitch(int)const override;
    void printValue() const override;
    private:
    const int timeOut = 40000;
    const double fullPeriod = 1000;
    const double offSetPeriod = 1000;
};

F_08A::F_08A(int channelNum, int* inputPorts, int timeOut, const char* name)
:receiver(name, channelNum, inputPorts), timeOut(timeOut)
{
    for(int i = 0; i < channelNum; i++)
    {
        pinMode(ports[i], INPUT);
    }
}

double F_08A::readValue(int channel) const
{
    //return pulseIn(ports[channel], HIGH);
    return (pulseIn(ports[channel], HIGH, timeOut) - offSetPeriod) / fullPeriod;
}

bool F_08A::readSwitch(int channel)const
{
    return pulseIn(ports[channel], HIGH) > offSetPeriod;
}

void F_08A::printValue() const
{

}

#endif
