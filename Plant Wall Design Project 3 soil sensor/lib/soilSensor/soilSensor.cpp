#include "SoilSensor.h"

int SoilSensor::TemperatureValue() {
  byte temp[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e};
  byte receivedData[9];
  Serial2.write(temp, sizeof(temp));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6];
  uint TemperatureValue = (float)soilTemperature / 10.0 * 100.0;
  // Serial.print("Soil Temperature: ");
  // Serial.println(TemperatureValue);\
  delay(10);
  return TemperatureValue;
}
int SoilSensor::HumidityValue() {
  byte humid[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e};
  byte receivedData[9];
  Serial2.write(humid, sizeof(humid));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];
  uint HumidityValue = (float)soilHumidity / 10.0 * 100.0;
  // Serial.print("Soil Humidity: ");
  // Serial.println(HumidityValue);
  return HumidityValue;
}
int SoilSensor::conductivity() {
  byte cond[] = {0x01,0x03,0x00,0x15,0x00,0x01,0x95,0xce}; 
  byte receivedData2[7];
  Serial2.write(cond, sizeof(cond));  // Send the query data to the NPK sensor
  Serial2.readBytes(receivedData2, sizeof(receivedData2));  // Read the received data into the receivedData array
  unsigned int RawConductivityValue = (receivedData2[3] << 8) | receivedData2[4];
  uint conductivityValue = (float)RawConductivityValue / 10.0 * 100.0;
  // Serial.print("Conductivity: ");
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
  unsigned int RawSoilPotassium = (receivedData4[7] << 8) | receivedData4[8];
  uint soilPotassium = (float)RawSoilPotassium / 10.0 * 100.0;
  // Serial.print("Potassium: ");
  // Serial.println(soilPotassium);
  return soilPotassium;
}








int SoilSensor::TemperatureValue2() {
  byte temp[] = {0x02,0x03,0x00,0x12,0x00,0x02,0x64,0x3D};
  byte receivedData[9];
  Serial2.write(temp, sizeof(temp));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  unsigned int soilTemperature2 = (receivedData[5] << 8) | receivedData[6];
  uint TemperatureValue2 = (float)soilTemperature2 / 10.0 * 100.0;
  // Serial.print("Soil Temperature2: ");
  // Serial.println(TemperatureValue2);
  return TemperatureValue2;
}
int SoilSensor::HumidityValue2() {
  byte humid[] = {0x02,0x03,0x00,0x12,0x00,0x02,0x64,0x3D};
  byte receivedData[9];
  Serial2.write(humid, sizeof(humid));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  // Serial.println("Received Data:");
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];
  uint HumidityValue = (float)soilHumidity / 10.0 * 100.0;
  // Serial.print("Soil Humidity2: ");
  // Serial.println(HumidityValue);
  delay(10);
  return HumidityValue;
}
int SoilSensor::conductivity2() {
  byte cond[] = {0x02,0x03,0x00,0x15,0x00,0x01,0x95,0xFD}; 
  byte receivedData2[7];
  Serial2.write(cond, sizeof(cond));  // Send the query data to the NPK sensor
  Serial2.readBytes(receivedData2, sizeof(receivedData2));  // Read the received data into the receivedData array
  unsigned int RawConductivityValue = (receivedData2[3] << 8) | receivedData2[4];
  uint conductivityValue = (float)RawConductivityValue / 10.0 * 100.0;
  // Serial.print("Conductivity2: ");
  // Serial.println(conductivityValue);
  return conductivityValue;

}
int SoilSensor::pH2() {
  byte pH[] = {0x02,0x03,0x00,0x06,0x00,0x01,0x64,0x38}; 
  byte receivedData3[7];
  Serial2.write(pH, sizeof(pH));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData3, sizeof(receivedData3));  // Read the received data into the receivedData array
  unsigned int RawSoilpHValue = (receivedData3[3] << 8) | receivedData3[4];
  uint soilpHValue = (float)RawSoilpHValue / 100.0 * 100.0;
  // Serial.print("pH2: ");
  // Serial.println(soilpHValue);
  return soilpHValue;
}
int SoilSensor::nitrogen2() {
  byte nitrogen[] = {0x02,0x03,0x00,0x1E,0x00,0x03,0x65,0xFE}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilNitrogen = (receivedData4[3] << 8) | receivedData4[4];
  uint soilNitrogen = (float)RawSoilNitrogen / 10.0 * 100.0;
  // Serial.print("Nitrogen2: ");
  // Serial.println(soilNitrogen);
  return soilNitrogen;
}
int SoilSensor::Phosphorus2() {
  byte nitrogen[] = {0x02,0x03,0x00,0x1E,0x00,0x03,0x65,0xFE}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilPhosphorus = (receivedData4[5] << 8) | receivedData4[6];
  uint soilPhosphorus = (float)RawSoilPhosphorus / 10.0 * 100.0;
  // Serial.print("Phosphorus2: ");
  // Serial.println(soilPhosphorus);
  return soilPhosphorus;
}
int SoilSensor::Potassium2() {
  byte nitrogen[] = {0x02,0x03,0x00,0x1E,0x00,0x03,0x65,0xFE}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilPotassium = (receivedData4[7] << 8) | receivedData4[8];
  uint soilPotassium = (float)RawSoilPotassium / 10.0 * 100.0;
  // Serial.print("Potassium: ");
  // Serial.println(soilPotassium);
  return soilPotassium;
}









int SoilSensor::TemperatureValue3() {
  byte temp[] = {0x03,0x03,0x00,0x12,0x00,0x02,0x65,0xec};
  byte receivedData[9];
  Serial2.write(temp, sizeof(temp));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6];
  uint TemperatureValue = (float)soilTemperature / 10.0 * 100.0;
  // Serial.print("Soil Temperature3: ");
  // Serial.println(TemperatureValue);
  delay(10);
  return TemperatureValue;
}
int SoilSensor::HumidityValue3() {
  byte humid[] = {0x03,0x03,0x00,0x12,0x00,0x02,0x65,0xec};
  byte receivedData[9];
  Serial2.write(humid, sizeof(humid));
  Serial2.readBytes(receivedData, sizeof(receivedData));
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];
  uint HumidityValue = (float)soilHumidity / 10.0 * 100.0;
  // Serial.print("Soil Humidity3: ");
  // Serial.println(HumidityValue);
  return HumidityValue;
}
int SoilSensor::conductivity3() {
  byte cond[] = {0x03,0x03,0x00,0x15,0x00,0x01,0x94,0x2c}; 
  byte receivedData2[7];
  Serial2.write(cond, sizeof(cond));  // Send the query data to the NPK sensor
  Serial2.readBytes(receivedData2, sizeof(receivedData2));  // Read the received data into the receivedData array
  unsigned int RawConductivityValue = (receivedData2[3] << 8) | receivedData2[4];
  uint conductivityValue = (float)RawConductivityValue / 10.0 * 100.0;
  // Serial.print("Conductivity3: ");
  // Serial.println(conductivityValue);
  return conductivityValue;
}
int SoilSensor::pH3() {
  byte pH[] = {0x03,0x03,0x00,0x06,0x00,0x01,0x65,0xe9}; 
  byte receivedData3[7];
  Serial2.write(pH, sizeof(pH));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData3, sizeof(receivedData3));  // Read the received data into the receivedData array
  unsigned int RawSoilpHValue = (receivedData3[3] << 8) | receivedData3[4];
  uint soilpHValue = (float)RawSoilpHValue / 100.0 * 100.0;
  // Serial.print("pH3: ");
  // Serial.println(soilpHValue);
  return soilpHValue;
}
int SoilSensor::nitrogen3() {
  byte nitrogen[] = {0x03,0x03,0x00,0x1E,0x00,0x03,0x64,0x2F}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilNitrogen = (receivedData4[3] << 8) | receivedData4[4];
  uint soilNitrogen = (float)RawSoilNitrogen / 10.0 * 100.0;
  // Serial.print("Nitrogen3: ");
  // Serial.println(soilNitrogen);
  return soilNitrogen;
}
int SoilSensor::Phosphorus3() {
  byte nitrogen[] = {0x03,0x03,0x00,0x1E,0x00,0x03,0x64,0x2f}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilPhosphorus = (receivedData4[5] << 8) | receivedData4[6];
  uint soilPhosphorus = (float)RawSoilPhosphorus / 10.0 * 100.0;
  // Serial.print("Phosphorus3: ");
  // Serial.println(soilPhosphorus);
  return soilPhosphorus;
}
int SoilSensor::Potassium3() {
  byte nitrogen[] = {0x03,0x03,0x00,0x1E,0x00,0x03,0x64,0x2f}; 
  byte receivedData4[11];
  Serial2.write(nitrogen, sizeof(nitrogen));  // Send the query data to the NPK sensor
  unsigned long startMillis = millis();  // Get the current time in milliseconds
  unsigned long delayTime = 1000;  // Set the desired delay time in milliseconds
  static unsigned long previousMillis = 0;  // Variable to store the previous time
  Serial2.readBytes(receivedData4, sizeof(receivedData4));  // Read the received data into the receivedData array
  unsigned int RawSoilPotassium = (receivedData4[7] << 8) | receivedData4[8];
  uint soilPotassium = (float)RawSoilPotassium / 10.0 * 100.0;
  // Serial.print("Potassium3: ");
  // Serial.println(soilPotassium);
  return soilPotassium;
}