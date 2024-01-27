#include "SoilSensor.h"

void conductivity() {
  byte cond[] = {0x01,0x03,0x00,0x15,0x00,0x01,0x95,0xce}; 
  byte receivedData2[7];

  Serial2.write(cond, sizeof(cond));  // Send the query data to the NPK sensor

  unsigned long startMillis = millis();  // Get the current time in milliseconds
  // while (millis() - startMillis < 1000) {
    Serial2.readBytes(receivedData2, sizeof(receivedData2));  // Read the received data into the receivedData array

    // Parse and print the received data in decimal format
    unsigned int soilConductivity = (receivedData2[3] << 8) | receivedData2[4];
    soilConductivity= (float)soilConductivity / 10.0;
    Serial.print("Soil conductivity: ");
    Serial.println(soilConductivity);
    delay(1000);
  // }
}

void pH() {
  byte pH[] = {0x01,0x03,0x00,0x06,0x00,0x01,0x64,0x0b}; 
  byte receivedData3[7];

  Serial2.write(pH, sizeof(pH));  // Send the query data to the NPK sensor

  unsigned long startMillis = millis();  // Get the current time in milliseconds
  // while (millis() - startMillis < 1000) {

    Serial2.readBytes(receivedData3, sizeof(receivedData3));  // Read the received data into the receivedData array

    // Parse and print the received data in decimal format
    unsigned int soilpH = (receivedData3[3] << 8) | receivedData3[4];

    Serial.print("Soil pH: ");
    Serial.println((float)soilpH / 100.0);
    delay(1000);
  // }
}

void nitrogen() {
  byte nitrogen[] = {0x01,0x03,0x00,0x1E,0x00,0x03,0x65,0xcd}; 
  byte receivedData4[11];

  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  // while (millis() - startMillis < 1000) {
    Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array

    // Parse and print the received data in decimal format
    unsigned int soilNitrogen = (receivedData4[3] << 8) | receivedData4[4];
    unsigned int soilPhosphorus = (receivedData4[5] << 8) | receivedData4[6];
    unsigned int soilPotassium = (receivedData4[7] << 8) | receivedData4[8];

    Serial.print("Soil Nitrogen: ");
    Serial.println((float)soilNitrogen / 10.0);
    Serial.print("Soil Phosphorus: ");
    Serial.println((float)soilPhosphorus / 10.0);
    Serial.print("Soil Potassium: ");
    Serial.println((float)soilPotassium / 10.0);
    delay(1000);
  // }
}
