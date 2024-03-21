#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "FlowSensor.h"
#include "msg.h"
#include "soilSensor.h"
#include "solenoidValve.h"
#include "UltrasonicSensor.h"
#include "waterPump.h"
#include "pinmap.h"

byte SuperPlant[45] = {};

FlowSensor flowSensor(FlowSensor1);
FlowSensor flowSensor2(FlowSensor2);
FlowSensor flowSensor3(FlowSensor3);

SolenoidValve Valve1(solenoidValve1);
SolenoidValve Valve2(solenoidValve2);
SolenoidValve Valve3(solenoidValve3);

waterPump pump(waterPumpPinA, waterPumpPinB);
UltrasonicSensor waterLevelSensor(trigPin, echoPin);

SoilSensor mySoilSensor;

int humidity_target = 3000;

unsigned long previousMillis = 0;
const long interval = 1000; // Interval in milliseconds

void valveInit(){
  Valve1.initializeValve();
  Valve2.initializeValve();
  Valve3.initializeValve();
}

void OpenPump(){
  pump.pumpRate(90);
}

void ClosePump(){
  pump.pumpRate(0);
}

void initializeSerial() {
  Serial.begin(9600);
  Serial2.begin(9600); 
}

void setup() {
  initializeSerial();
  flowSensor.begin();
  valveInit(); // Configure solenoid valve
  waterLevelSensor.begin();// Configure ultrasonic sensor
  pump.initializePump(); // Initialize the pump
}

void controlSensor(int humidity, int targetHumidity, FlowSensor &flowSensor, SolenoidValve &valve, waterPump &pump) {
  if (humidity < targetHumidity) {
    OpenPump();
    flowSensor.getflowRate();
    if (flowSensor.totalMilliLitres < flowSensor.TargetValue) {
      valve.valveOpen();
    } else {
      valve.valveClose();
      ClosePump();
      flowSensor.reset();
    }
  } else {
    valve.valveClose();
    ClosePump();
  }
}


void loop() {  
  // Check if it's time to read the sensors
  int temperature = mySoilSensor.TemperatureValue();
  int humidity = mySoilSensor.HumidityValue();
  int conductivity = mySoilSensor.conductivity();
  int pHValue = mySoilSensor.pH();
  int nitrogenValue = mySoilSensor.nitrogen();
  int phosphorusValue = mySoilSensor.Phosphorus();
  int potassiumValue = mySoilSensor.Potassium();
  
  int temperature2 = mySoilSensor.TemperatureValue2();
  int humidity2 = mySoilSensor.HumidityValue2();
  int conductivity2 = mySoilSensor.conductivity2();
  int pHValue2 = mySoilSensor.pH2();
  int nitrogenValue2 = mySoilSensor.nitrogen2();
  int phosphorusValue2 = mySoilSensor.Phosphorus2();
  int potassiumValue2 = mySoilSensor.Potassium2();

  int temperature3 = mySoilSensor.TemperatureValue3();
  int humidity3 = mySoilSensor.HumidityValue3();
  int conductivity3 = mySoilSensor.conductivity3();
  int pHValue3 = mySoilSensor.pH3();
  int nitrogenValue3 = mySoilSensor.nitrogen3();
  int phosphorusValue3 = mySoilSensor.Phosphorus3();
  int potassiumValue3 = mySoilSensor.Potassium3();

  int waterLevel = waterLevelSensor.getDistance();
  
  delay(1000);

  SuperPlant[ 0] = (byte)0xff;
  SuperPlant[ 1] = (byte)((temperature & 0xFF00) >> 8);
  SuperPlant[ 2] = (byte)((temperature & 0x00FF));
  SuperPlant[ 3] = (byte)((humidity & 0xFF00) >> 8);
  SuperPlant[ 4] = (byte)((humidity & 0x00FF));
  SuperPlant[ 5] = (byte)((conductivity & 0xFF00) >> 8);
  SuperPlant[ 6] = (byte)((conductivity & 0x00FF));
  SuperPlant[ 7] = (byte)((pHValue & 0xFF00) >> 8);
  SuperPlant[ 8] = (byte)((pHValue & 0x00FF));
  SuperPlant[ 9] = (byte)((nitrogenValue & 0xFF00) >> 8);
  SuperPlant[10] = (byte)((nitrogenValue & 0x00FF));
  SuperPlant[11] = (byte)((phosphorusValue & 0xFF00) >> 8);
  SuperPlant[12] = (byte)((phosphorusValue & 0x00FF));
  SuperPlant[13] = (byte)((potassiumValue & 0xFF00) >> 8);
  SuperPlant[14] = (byte)((potassiumValue & 0x00FF));
  SuperPlant[15] = (byte)((waterLevel & 0xFF00) >> 8);
  SuperPlant[16] = (byte)((waterLevel & 0x00FF));
  SuperPlant[17] = (byte)((temperature2 & 0xFF00) >> 8);
  SuperPlant[18] = (byte)((temperature2 & 0x00FF));
  SuperPlant[19] = (byte)((humidity2 & 0xFF00) >> 8);
  SuperPlant[20] = (byte)((humidity2 & 0x00FF));
  SuperPlant[21] = (byte)((conductivity2 & 0xFF00) >> 8);
  SuperPlant[22] = (byte)((conductivity2 & 0x00FF));
  SuperPlant[23] = (byte)((pHValue2 & 0xFF00) >> 8);
  SuperPlant[24] = (byte)((pHValue2 & 0x00FF));
  SuperPlant[25] = (byte)((nitrogenValue2 & 0xFF00) >> 8);
  SuperPlant[26] = (byte)((nitrogenValue2 & 0x00FF));
  SuperPlant[27] = (byte)((phosphorusValue2 & 0xFF00) >> 8);
  SuperPlant[28] = (byte)((phosphorusValue2 & 0x00FF));
  SuperPlant[29] = (byte)((potassiumValue2 & 0xFF00) >> 8);
  SuperPlant[30] = (byte)((potassiumValue2 & 0x00FF));
  SuperPlant[31] = (byte)((temperature3 & 0xFF00) >> 8);
  SuperPlant[32] = (byte)((temperature3 & 0x00FF));
  SuperPlant[33] = (byte)((humidity3 & 0xFF00) >> 8);
  SuperPlant[34] = (byte)((humidity3 & 0x00FF));
  SuperPlant[35] = (byte)((conductivity3 & 0xFF00) >> 8);
  SuperPlant[36] = (byte)((conductivity3 & 0x00FF));
  SuperPlant[37] = (byte)((pHValue3 & 0xFF00) >> 8);
  SuperPlant[38] = (byte)((pHValue3 & 0x00FF));
  SuperPlant[39] = (byte)((nitrogenValue3 & 0xFF00) >> 8);
  SuperPlant[40] = (byte)((nitrogenValue3 & 0x00FF));
  SuperPlant[41] = (byte)((phosphorusValue3 & 0xFF00) >> 8);
  SuperPlant[42] = (byte)((phosphorusValue3 & 0x00FF));
  SuperPlant[43] = (byte)((potassiumValue3 & 0xFF00) >> 8);
  SuperPlant[44] = (byte)((potassiumValue3 & 0x00FF));
  Serial.write(SuperPlant, sizeof(SuperPlant));

  controlSensor(humidity, humidity_target, flowSensor, Valve1, pump);
  delay(1000);
  controlSensor(humidity2, humidity_target, flowSensor2, Valve2, pump);
  delay(1000);
  controlSensor(humidity3, humidity_target, flowSensor3, Valve3, pump);
}



// void loop() {
//   int temperature = mySoilSensor.TemperatureValue();
//   int humidity = mySoilSensor.HumidityValue();
//   int conductivity = mySoilSensor.conductivity();
//   int pHValue = mySoilSensor.pH();
//   int nitrogenValue = mySoilSensor.nitrogen();
//   int phosphorusValue = mySoilSensor.Phosphorus();
//   int potassiumValue = mySoilSensor.Potassium();
  
//   int temperature2 = mySoilSensor.TemperatureValue2();
//   int humidity2 = mySoilSensor.HumidityValue2();
//   int conductivity2 = mySoilSensor.conductivity2();
//   int pHValue2 = mySoilSensor.pH2();
//   int nitrogenValue2 = mySoilSensor.nitrogen2();
//   int phosphorusValue2 = mySoilSensor.Phosphorus2();
//   int potassiumValue2 = mySoilSensor.Potassium2();

//   int temperature3 = mySoilSensor.TemperatureValue3();
//   int humidity3 = mySoilSensor.HumidityValue3();
//   int conductivity3 = mySoilSensor.conductivity3();
//   int pHValue3 = mySoilSensor.pH3();
//   int nitrogenValue3 = mySoilSensor.nitrogen3();
//   int phosphorusValue3 = mySoilSensor.Phosphorus3();
//   int potassiumValue3 = mySoilSensor.Potassium3();

//   int waterLevel = waterLevelSensor.getDistance();
  
//   delay(1000);

//   SuperPlant[ 0] = (byte)0xff;
//   SuperPlant[ 1] = (byte)((temperature & 0xFF00) >> 8);
//   SuperPlant[ 2] = (byte)((temperature & 0x00FF));
//   SuperPlant[ 3] = (byte)((humidity & 0xFF00) >> 8);
//   SuperPlant[ 4] = (byte)((humidity & 0x00FF));
//   SuperPlant[ 5] = (byte)((conductivity & 0xFF00) >> 8);
//   SuperPlant[ 6] = (byte)((conductivity & 0x00FF));
//   SuperPlant[ 7] = (byte)((pHValue & 0xFF00) >> 8);
//   SuperPlant[ 8] = (byte)((pHValue & 0x00FF));
//   SuperPlant[ 9] = (byte)((nitrogenValue & 0xFF00) >> 8);
//   SuperPlant[10] = (byte)((nitrogenValue & 0x00FF));
//   SuperPlant[11] = (byte)((phosphorusValue & 0xFF00) >> 8);
//   SuperPlant[12] = (byte)((phosphorusValue & 0x00FF));
//   SuperPlant[13] = (byte)((potassiumValue & 0xFF00) >> 8);
//   SuperPlant[14] = (byte)((potassiumValue & 0x00FF));
//   SuperPlant[15] = (byte)((waterLevel & 0xFF00) >> 8);
//   SuperPlant[16] = (byte)((waterLevel & 0x00FF));
//   SuperPlant[17] = (byte)((temperature2 & 0xFF00) >> 8);
//   SuperPlant[18] = (byte)((temperature2 & 0x00FF));
//   SuperPlant[19] = (byte)((humidity2 & 0xFF00) >> 8);
//   SuperPlant[20] = (byte)((humidity2 & 0x00FF));
//   SuperPlant[21] = (byte)((conductivity2 & 0xFF00) >> 8);
//   SuperPlant[22] = (byte)((conductivity2 & 0x00FF));
//   SuperPlant[23] = (byte)((pHValue2 & 0xFF00) >> 8);
//   SuperPlant[24] = (byte)((pHValue2 & 0x00FF));
//   SuperPlant[25] = (byte)((nitrogenValue2 & 0xFF00) >> 8);
//   SuperPlant[26] = (byte)((nitrogenValue2 & 0x00FF));
//   SuperPlant[27] = (byte)((phosphorusValue2 & 0xFF00) >> 8);
//   SuperPlant[28] = (byte)((phosphorusValue2 & 0x00FF));
//   SuperPlant[29] = (byte)((potassiumValue2 & 0xFF00) >> 8);
//   SuperPlant[30] = (byte)((potassiumValue2 & 0x00FF));
//   SuperPlant[31] = (byte)((temperature3 & 0xFF00) >> 8);
//   SuperPlant[32] = (byte)((temperature3 & 0x00FF));
//   SuperPlant[33] = (byte)((humidity3 & 0xFF00) >> 8);
//   SuperPlant[34] = (byte)((humidity3 & 0x00FF));
//   SuperPlant[35] = (byte)((conductivity3 & 0xFF00) >> 8);
//   SuperPlant[36] = (byte)((conductivity3 & 0x00FF));
//   SuperPlant[37] = (byte)((pHValue3 & 0xFF00) >> 8);
//   SuperPlant[38] = (byte)((pHValue3 & 0x00FF));
//   SuperPlant[39] = (byte)((nitrogenValue3 & 0xFF00) >> 8);
//   SuperPlant[40] = (byte)((nitrogenValue3 & 0x00FF));
//   SuperPlant[41] = (byte)((phosphorusValue3 & 0xFF00) >> 8);
//   SuperPlant[42] = (byte)((phosphorusValue3 & 0x00FF));
//   SuperPlant[43] = (byte)((potassiumValue3 & 0xFF00) >> 8);
//   SuperPlant[44] = (byte)((potassiumValue3 & 0x00FF));
//   Serial.write(SuperPlant, sizeof(SuperPlant));

//   // Soil Humidity Contrl Pump
//   if (humidity < humidity_target) {
//     OpenPump();

//     // Get Flowrate control Valve
//     flowSensor.getflowRate();
//     if (flowSensor.totalMilliLitres < flowSensor.TargetValue) {
//       Valve1.valveOpen();
//       }
//     else if(flowSensor.totalMilliLitres >= flowSensor.TargetValue) {
//         Valve1.valveClose();
//         pump.pumpRate(0);
//         flowSensor.reset();
//       }
//   }
//   else if (humidity >= humidity_target){
//     Valve1.valveClose();
//     pump.pumpRate(0);
//   }

//   if (humidity2 < humidity_target) {
//     OpenPump();

//     // Get Flowrate control Valve
//     flowSensor2.getflowRate();
//     if (flowSensor2.totalMilliLitres < flowSensor2.TargetValue) {
//       Valve2.valveOpen();
//       }
//     else if(flowSensor2.totalMilliLitres >= flowSensor2.TargetValue) {
//         Valve2.valveClose();
//         pump.pumpRate(0);
//         flowSensor2.reset();
//       }
//   }
//   else if (humidity2 >= humidity_target){
//     Valve2.valveClose();
//     pump.pumpRate(0);
//   }

//   if (humidity3 < humidity_target) {
//     OpenPump();

//     // Get Flowrate control Valve
//     flowSensor3.getflowRate();
//     if (flowSensor3.totalMilliLitres < flowSensor3.TargetValue) {
//       Valve3.valveOpen();
//       }
//     else if(flowSensor3.totalMilliLitres >= flowSensor3.TargetValue) {
//         Valve3.valveClose();
//         pump.pumpRate(0);
//         flowSensor3.reset();
//       }
//   }
//   else if (humidity3 >= humidity_target){
//     Valve3.valveClose();
//     pump.pumpRate(0);
//   }
// }