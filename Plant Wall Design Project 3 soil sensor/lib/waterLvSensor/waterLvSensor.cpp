#include "WaterLvSensor.h"

WaterLevelSensor::WaterLevelSensor(int _analogPin, double _voltageToLevelFactor) {
  analogPin = _analogPin;
  voltageToLevelFactor = _voltageToLevelFactor;
  pinMode(analogPin, INPUT);
}

void WaterLevelSensor::initialize() {
  // You can add any initialization logic here
}

double WaterLevelSensor::readVoltage() {
  int sensorValue = analogRead(analogPin);
  // Convert the sensor reading to voltage
  double voltage = sensorValue * (24.0 / 1023.0); // Assumes a 24V reference voltage

  return voltage;
}

double WaterLevelSensor::convertToWaterLevel(double voltage) {
  // Implement the conversion based on your sensor's calibration
  // For example, you might use a linear relationship or a lookup table
  double waterLevel = voltage * voltageToLevelFactor;
  return waterLevel;
}
