#include <Arduino.h>

#ifndef SOLENOID_VALVE_H
#define SOLENOID_VALVE_H

class SolenoidValve {
  public:
    SolenoidValve(uint8_t pin);
    void initializeValve();
    void valveOpen();
    void valveClose();

  private:
    uint8_t pin;
};

#endif