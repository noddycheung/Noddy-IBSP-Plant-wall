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

HardwareSerial* serial_;

void init(HardwareSerial* serial){ 
    serial = serial_;

    serial_->begin(9600);
    unsigned char encryptkey[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // unsigned char encryptkey[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

FlowSensor flowSensor(FlowSensor1);

SolenoidValve Valve1(solenoidValve1);
// SolenoidValve Valve2(solenoidValve2);
// SolenoidValve Valve3(solenoidValve3);

waterPump pump(waterPumpPinA, waterPumpPinB);
UltrasonicSensor waterLevelSensor(trigPin, echoPin);


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

  pump.initializePump(); // Initialize the pump

}

void loop() {
  //soilSensor
  byte temp[] = {0x01,0x03,0x00,0x12,0x00,0x02,0x64,0x0e}; //temp
  byte receivedData[9];

  Serial2.write(temp, sizeof(temp));  // Send the query data to the NPK sensor
  delay(1000);  // Wait for 1 second

  Serial2.readBytes(receivedData, sizeof(receivedData));  // Read the received data into the receivedData array

  // Parse and print the received data in decimal format
  unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6];
  unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];

  soilTemperature = ((float)soilTemperature / 10.0);
  soilHumidity = ((float)soilHumidity / 10.0);

  
  //Soil Humidity Contrl Pump
  if (soilHumidity < 30) {
    pump.pumpRate(90);

    // Get Flowrate control Valve
    flowSensor.getflowRate();
    if (flowSensor.totalMilliLitres < flowSensor.TargetValue) {
      Valve1.valveOpen();
      // Serial.println("Debug");
      }
    else if(flowSensor.totalMilliLitres >= flowSensor.TargetValue) {
        Valve1.valveClose();
        // Serial.println("Close Debug");
        pump.pumpRate(0);
        flowSensor.reset();
      }
  }
  else {
    pump.pumpRate(0);
  }


  conductivity(); // Call the conductivity function
  pH(); // Call the pH function
  nitrogen(); // Call the nitrogen function


  // ultrasonic
  waterLevelSensor.update();

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
  Serial.println("----------");
  delay(1000);
  


  if (Serial.available())
  {
      char data[8];
      // char data[16];
        data[0] = 0x01; //packet type is ack
        data[1] = highByte(soilTemperature);
        data[2] = highByte(soilHumidity);
        // data[3] = highByte(flowSensor.getflowRate()); //Transmitting/Source Station ID highByte
        // data[4] = highByte(waterLevelSensor.update()); //Transmitting/Source Station ID lowByte
        // data[5] = buf[5];
        // data[6] = buf[6];
        // data[7] = buf[6];
        // data[8] = buf[6];
        // data[9] = buf[6];
        // data[10] = buf[6];
        // data[11] = buf[6];
        // data[12] = buf[6];
        // data[13] = buf[6];
        // data[14] = buf[6];
        // data[15] = buf[6];
        data[7] = 0x00;
        // Serial.println(data);
        serial_->write(data, sizeof(data));
      }
    else
    {
      Serial.println("Receive failed");
    }
}

