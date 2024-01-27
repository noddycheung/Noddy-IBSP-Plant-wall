#include "FlowSensor.h"

// define the static member variable here, outside the class
volatile long FlowSensor::pulse = 0;

FlowSensor::FlowSensor(int pin) {
  sensorPin = pin; // set the pin number
  lastTime = 0; // initialize the last time
  flowRate = 0; // initialize the flowRate
  totalMilliLitres = 0;
}

void FlowSensor::begin() {
  pinMode(sensorPin, INPUT); // set the pin mode
  attachInterrupt(digitalPinToInterrupt(sensorPin), FlowSensor::increase, RISING); // attach the interrupt handler
}

void FlowSensor::getflowRate() {
    if(millis() - lastTime >= 1000){
    // update the flowRate every second
    // Serial.println("valve high");
    flowRate = (pulse * 1000 / 60 / 11); // (Pulse frequency x 1000 mL) / 60 min / 11Q = flowrate in mL/s
    //flowRate = (pulse * 60 / 11); // (Pulse frequency x 60 min) / 11Q = flowrate in L/hour
    Serial.print("Water Flow Per Sec:  ");
    Serial.print(flowRate);
    Serial.println(" mL/s   ");
    //Serial.print(" L/h    ");
    lastTime = millis(); // update the last time

    //calculate volume
    totalMilliLitres += flowRate;
    // Serial.print("Total Volume:  ");
    // Serial.print(totalMilliLitres);
    // Serial.println(" mL   ");
    
    // Print the cumulative total of litres flowed since starting
    // return totalMilliLitres;
    pulse = 0; // reset the pulse
    }
  }

void FlowSensor::increase() {
  pulse++; // increment the pulse
}

void FlowSensor::reset(){
    lastTime = 0;
    flowRate = 0;
    totalMilliLitres = 0;
    pulse = 0;    
}