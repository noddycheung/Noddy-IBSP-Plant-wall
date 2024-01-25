#include "dht22.h"
#include <Arduino.h>

DHTSensor::DHTSensor(int pin, int dhtType, unsigned long intervalMillis)
  : dht(pin, dhtType), interval(intervalMillis) {}

void DHTSensor::initialize() {
  dht.begin();
  previousMillis = 0; 
  temperature = 0;
  humidity = 0;
}

void DHTSensor::update() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Read temperature
    float newT = dht.readTemperature();
    if (isnan(newT)) {
      Serial.println("Failed to read temperature from DHT sensor!");
    } else {
      temperature = newT;
      
      // Print temperature
      Serial.print("Temperature: ");
      Serial.print(temperature); 
      Serial.println("°C");
    }
    
    // Read humidity  
    float newH = dht.readHumidity();
    if (isnan(newH)) {
      Serial.println("Failed to read humidity from DHT sensor!");
    } else {
      humidity = newH;
      
      // Print humidity
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println("%");
    }
  }
}

float DHTSensor::getTemperature() {
  return temperature; 
}

float DHTSensor::getHumidity() {
  return humidity;
}
