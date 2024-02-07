#include "SoilSensor.h"

int SoilSensor::TemperatureValue() {
  byte temp[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e};
  byte receivedData[9];
  // Replace Serial2 with a parameter passed to the function
  Serial2.write(temp, sizeof(temp));
  // delay(1000);
  // Replace Serial2 with a parameter passed to the function
  Serial2.readBytes(receivedData, sizeof(receivedData));
  // Serial.println("Received Data:");
  unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6];
  // Serial.print("Soil Temperature: ");
  uint TemperatureValue = (float)soilTemperature / 10.0 * 100.0;
  // Serial.println(TemperatureValue);
  return TemperatureValue;
}
int SoilSensor::HumidityValue() {
  byte temp[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e};
  byte receivedData[9];
  // Replace Serial2 with a parameter passed to the function
  Serial2.write(temp, sizeof(temp));
  // delay(1000);
  // Replace Serial2 with a parameter passed to the function
  Serial2.readBytes(receivedData, sizeof(receivedData));
  // Serial.println("Received Data:");
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];

  // Serial.print("Soil Humidity: ");
  uint HumidityValue = (float)soilHumidity / 10.0 * 100.0;
  // Serial.println(HumidityValue);
  return HumidityValue;
}
int SoilSensor::conductivity() {
  byte cond[] = {0x01,0x03,0x00,0x15,0x00,0x01,0x95,0xce}; 
  byte receivedData2[7];
  Serial2.write(cond, sizeof(cond));  // Send the query data to the NPK sensor
  Serial2.readBytes(receivedData2, sizeof(receivedData2));  // Read the received data into the receivedData array
  // Parse and print the received data in decimal format
  unsigned int RawConductivityValue = (receivedData2[3] << 8) | receivedData2[4];
  // Serial.print("Conductivity: ");
  uint conductivityValue = (float)RawConductivityValue / 10.0 * 100.0;
  // Serial.println(conductivityValue);
  return conductivityValue;

}
int SoilSensor::pH() {
  byte pH[] = {0x01,0x03,0x00,0x06,0x00,0x01,0x64,0x0b}; 
  byte receivedData3[7];
  Serial2.write(pH, sizeof(pH));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData3, sizeof(receivedData3));  // Read the received data into the receivedData array
  // Parse and print the received data in decimal format
  unsigned int RawSoilpHValue = (receivedData3[3] << 8) | receivedData3[4];
  uint soilpHValue = (float)RawSoilpHValue / 100.0 * 100.0;

  // Serial.print("pH: ");
  // Serial.println(soilpHValue);
  return soilpHValue;
}
int SoilSensor::nitrogen() {
  byte nitrogen[] = {0x01,0x03,0x00,0x1E,0x00,0x03,0x65,0xcd}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor

  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  // Parse and print the received data in decimal format
  unsigned int RawSoilNitrogen = (receivedData4[3] << 8) | receivedData4[4];
 
  uint soilNitrogen = (float)RawSoilNitrogen / 10.0 * 100.0;
  // Serial.print("Nitrogen: ");
  // Serial.println(soilNitrogen);
  return soilNitrogen;
}
int SoilSensor::Phosphorus() {
  byte nitrogen[] = {0x01,0x03,0x00,0x1E,0x00,0x03,0x65,0xcd}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor

  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  // Parse and print the received data in decimal format
  unsigned int RawSoilPhosphorus = (receivedData4[5] << 8) | receivedData4[6];
 
  uint soilPhosphorus = (float)RawSoilPhosphorus / 10.0 * 100.0;
  // Serial.print("Phosphorus: ");
  // Serial.println(soilPhosphorus);
  return soilPhosphorus;
}
int SoilSensor::Potassium() {
  byte nitrogen[] = {0x01,0x03,0x00,0x1E,0x00,0x03,0x65,0xcd}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor

  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  // Parse and print the received data in decimal format
  unsigned int RawSoilPotassium = (receivedData4[7] << 8) | receivedData4[8];
  uint soilPotassium = (float)RawSoilPotassium / 10.0 * 100.0;
  // Serial.print("Potassium: ");
  // Serial.println(soilPotassium);
  return soilPotassium;
}