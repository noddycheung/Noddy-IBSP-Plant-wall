#ifndef FLOWSENSOR_H
#define FLOWSENSOR_H

#include <Arduino.h>

class FlowSensor {
  public:
    FlowSensor(int pin); // constructor
    void begin(); // initialize the sensor
    void getflowRate(); // get the flowRate in liters
    void reset();
    unsigned long totalMilliLitres = 0;
    float flowRate; // the flowRate in liters
    unsigned long TargetValue = 30;
  private:
    int sensorPin; // the pin number of the sensor
    static volatile long pulse; // the number of pulses from the sensor, make it static
    unsigned long lastTime; // the last time the pulse was updated
    // float flowRate; // the flowRate in liters

    static void increase(); // the interrupt handler function, also static
};

#endif