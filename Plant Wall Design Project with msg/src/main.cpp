#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "FlowSensor.h"
#include "msg.h"
#include "soilSensor.h"
#include "solenoidValve.h"
// #include "waterLvSensor.h"
#include "UltrasonicSensor.h"
#include "waterPump.h"
#include "pinmap.h"

// HardwareSerial* serial_;

byte SuperPlant[17] = {};

FlowSensor flowSensor(FlowSensor1);

SolenoidValve Valve1(solenoidValve1);
SolenoidValve Valve2(solenoidValve2);
SolenoidValve Valve3(solenoidValve3);

waterPump pump(waterPumpPinA, waterPumpPinB);
UltrasonicSensor waterLevelSensor(trigPin, echoPin);

SoilSensor mySoilSensor;


void pinSetup(){

};

void valveInit(){
  Valve1.initializeValve();
  Valve2.initializeValve();
  Valve3.initializeValve();
}

void testValve(){
  // digitalWrite(solenoidValve1, HIGH);
  Valve1.valveClose();
  Valve2.valveClose();
  Valve3.valveClose();
  delay(3000);
  // digitalWrite(solenoidValve1, LOW);
  Valve1.valveOpen();
  Valve2.valveOpen();
  Valve3.valveOpen();
  delay(1000);
}
/////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // NPK communicates at 9600 bps
  // soilSensor.begin(); // Initialize the communication with the soil sensor
  flowSensor.begin();
  pinSetup();
  waterLevelSensor.begin();// Configure ultrasonic sensor

  valveInit(); // Configure solenoid valve

  //nanoMsg.init(&Serial);
  // init(&Serial);

  pump.initializePump(); // Initialize the pump

}

void loop() {
  int temperature = mySoilSensor.TemperatureValue();
  int humidity = mySoilSensor.HumidityValue();
  int conductivity = mySoilSensor.conductivity();
  int pHValue = mySoilSensor.pH();
  int nitrogenValue = mySoilSensor.nitrogen();
  int phosphorusValue = mySoilSensor.Phosphorus();
  int potassiumValue = mySoilSensor.Potassium();
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
  Serial.write(SuperPlant, sizeof(SuperPlant));
  

// ///////////////////////////////////////////////////////////////


  // Soil Humidity Contrl Pump
  if (humidity < 3000) {
    // pump.pumpRate(90);

    // Get Flowrate control Valve
    flowSensor.getflowRate();
    if (flowSensor.totalMilliLitres < flowSensor.TargetValue) {
      Valve1.valveOpen();
      }
    else if(flowSensor.totalMilliLitres >= flowSensor.TargetValue) {
        Valve1.valveClose();
        pump.pumpRate(0);
        flowSensor.reset();
      }
  }
  else {
    Valve1.valveClose();
    pump.pumpRate(0);
  }

  // ultrasonic
  // waterLevelSensor.getDistance();

  //waterPump
  // pump.pumpRate(90);
  // delay(3000);
  // pump.pumpRate(0);

  //solenoid valve
  // testValve();

  //test flow sensor
  // flowSensor.getflowRate();

  // if(!nanoMsg.read()){
  //   return; 
  // }

}
