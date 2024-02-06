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

byte SuperPlant[9] = {};

// char a = 'a';
// printf((int)a); //97
// printf((byte)a); //0x61
// printf("%X", a);

FlowSensor flowSensor(FlowSensor1);

SolenoidValve Valve1(solenoidValve1);
// SolenoidValve Valve2(solenoidValve2);
// SolenoidValve Valve3(solenoidValve3);

waterPump pump(waterPumpPinA, waterPumpPinB);
UltrasonicSensor waterLevelSensor(trigPin, echoPin);

SoilSensor soilSensor();


void pinSetup(){

};

void valveInit(){
  Valve1.initializeValve();
  // Valve2.initializeValve();
  // Valve3.initializeValve();
}

void testValve(){
  // digitalWrite(solenoidValve1, HIGH);
  Valve1.valveClose();
  // Valve2.valveClose();
  // Valve3.valveClose();
  delay(3000);
  // digitalWrite(solenoidValve1, LOW);
  Valve1.valveOpen();
  // Valve2.valveOpen();
  // Valve3.valveOpen();
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
  //soilSensor
  byte temp[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e}; //temp
  byte receivedData[9];

  Serial2.write(temp, sizeof(temp));  // Send the query data to the NPK sensor2
  delay(1000);  // Wait for 1 second

  Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the received data into the receivedData array
  Serial.println("Received Data:");

  // Parse and print the received data in decimal format
  unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6]; //uint16_t
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];

  Serial.print("Soil Temperature: ");
  uint TemperatureValue = (float)soilTemperature / 10.0 * 100.0;
  Serial.println(TemperatureValue);

  Serial.print("Soil Humidity: ");
  uint HumidityValue = (float)soilHumidity / 10.0 * 100.0;
  Serial.println(HumidityValue);

  //Soil Humidity Contrl Pump
  // if (soilHumidity < 3000) {
  //   pump.pumpRate(90);

  //   // Get Flowrate control Valve
  //   flowSensor.getflowRate();
  //   if (flowSensor.totalMilliLitres < flowSensor.TargetValue) {
  //     Valve1.valveOpen();
  //     // Serial.println("Debug");
  //     }
  //   else if(flowSensor.totalMilliLitres >= flowSensor.TargetValue) {
  //       Valve1.valveClose();
  //       // Serial.println("Close Debug");
  //       pump.pumpRate(0);
  //       flowSensor.reset();
  //     }
  // }
  // else {
  //   pump.pumpRate(0);
  // }

  // conductivity(); // Call the conductivity function
  // pH(); // Call the pH function
  // nitrogen(); // Call the nitrogen function


  // ultrasonic
  // waterLevelSensor.update();

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

  
  SuperPlant[0] = (byte)0xff;
  SuperPlant[1] = (byte)((TemperatureValue & 0xFF00) >> 8);
  SuperPlant[2] = (byte)((TemperatureValue & 0x00FF));
  SuperPlant[3] = (byte)((HumidityValue & 0xFF00) >> 8);
  SuperPlant[4] = (byte)((HumidityValue & 0x00FF));
  SuperPlant[5] = (byte)(0xff);
  SuperPlant[6] = (byte)(0xff);
  SuperPlant[7] = (byte)(0xff);
  SuperPlant[8] = (byte)(0xff);
  Serial.write(SuperPlant, sizeof(SuperPlant));


  Serial.println("----------");
  delay(1000);
  // float printsoiltemp;
  // unsigned char const * p = reinterpret_cast<unsigned char const *> (&printsoiltemp);
  // for (std::size_t i = 0; i != sizeof (float); ++i) {
  //     std::printf ("The byte #%zu is 0x%02X\n", i, p [i]);
  // }

}
