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

    int TemperatureValue2();
    int HumidityValue2();
    int conductivity2();
    int pH2();
    int nitrogen2();
    int Phosphorus2();
    int Potassium2();

    int TemperatureValue3();
    int HumidityValue3();
    int conductivity3();
    int pH3();
    int nitrogen3();
    int Phosphorus3();
    int Potassium3();
    
  private:
  
};

#endif
