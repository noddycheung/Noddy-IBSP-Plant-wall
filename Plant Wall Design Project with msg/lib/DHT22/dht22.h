#include <DHT.h>
#include <Arduino.h>

#ifndef _DHTSENSOR_H
#define _DHTSENSOR_H

class DHTSensor {
private:
  unsigned long previousMillis;
  unsigned long interval = 1000;
  float temperature;
  float humidity;
  DHT dht;

public:
  DHTSensor(int pin, int dhtType, unsigned long intervalMillis);

  void initialize();
  void update();
  float getTemperature();
  float getHumidity();
};

#endif