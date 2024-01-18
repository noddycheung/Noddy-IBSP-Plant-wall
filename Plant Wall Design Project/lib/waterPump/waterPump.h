#include <Arduino.h>

#ifndef _WATERPUMP_H
#define _WATERPUMP_H


class waterPump{
    private:
    int waterPumpPinA;
    int waterPumpPinB;
    //int pumpPWM;
    const int pwmFreq = 20000;
    const int PWMResolution = 8; // Esp32 Resolution 8 bit
    //const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);
    const int pwmChannelA = 1;
    const int pwmChannelB = 2;
    float minRate = 0.0f;
    float maxRate = 98.0f;

    public:
    waterPump(int waterPumpPinA, int waterPumpPinB);
    void initializePump();
    void pumpRate(int pwmValue);
    void stopPump();
};

#endif


