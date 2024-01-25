#ifndef _WATERLVSENSOR_H
#define _WATERLVSENSOR_H

#include "Arduino.h"

class WaterLevelSensor {
  private:
    int analogPin; // Pin for reading voltage
    double voltageToLevelFactor; // Conversion factor
    double MaximumWaterLevel = 0;
    double MinimumWaterLevel = 0;

  public:
    WaterLevelSensor(int _analogPin, double _voltageToLevelFactor);
    void initialize();
    double readVoltage();
    double convertToWaterLevel(double voltage);
};

#endif
