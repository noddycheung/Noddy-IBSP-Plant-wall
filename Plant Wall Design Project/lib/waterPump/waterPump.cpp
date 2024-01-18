#include "waterPump.h"

waterPump::waterPump(int waterPumpPinA, int waterPumpPinB) {
  this->waterPumpPinA = waterPumpPinA;
  this->waterPumpPinB = waterPumpPinB;
  pinMode(waterPumpPinA, OUTPUT);
  pinMode(waterPumpPinB, OUTPUT);
}

// Initialize the pump
// Currently at 1k Freq, to be done later
void waterPump::initializePump() {
  // Code to initialize the pump
  // ledcSetup(pwmChannelA, pwmFreq, PWMResolution);
  // ledcSetup(pwmChannelB, pwmFreq, PWMResolution);
  // ledcAttachPin(waterPumpPinA, pwmChannelA);
  // ledcAttachPin(waterPumpPinB, pwmChannelB);
  stopPump();
}

void waterPump::pumpRate(int pwmValue){
  pwmValue = constrain(pwmValue, minRate, maxRate); // Ensure rate is within the defined range
  pwmValue = map(pwmValue, minRate, maxRate, 0, (255*maxRate/100)); // Map percentage to PWM value

  analogWrite(waterPumpPinA, pwmValue);
  analogWrite(waterPumpPinB, minRate); // Pump Pin B should be 0
}

// Stop the pump
void waterPump::stopPump() {
  // Code to stop the pump
  pumpRate(0);
}