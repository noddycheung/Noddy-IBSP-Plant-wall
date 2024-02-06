#ifndef SOILSENSOR_H
#define SOILSENSOR_H

#include <Arduino.h>

class SoilSensor {
  public:
    int TemperatureValue();
    int HumidityValue();
    int conductivity();
    int pH();
    int nitrogen();
    int Phosphorus();
    int Potassium();
  private:
  
};

#endif
