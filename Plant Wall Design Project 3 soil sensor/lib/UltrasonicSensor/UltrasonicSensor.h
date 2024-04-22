#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(uint8_t rxPin, uint8_t txPin);
    void begin();
    float readDistance();

private:
    SoftwareSerial ss;
};

#endif
