#include "SolenoidValve.h"

SolenoidValve::SolenoidValve(uint8_t pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void SolenoidValve::initializeValve() {
  valveClose();
}

void SolenoidValve::valveOpen() {
  digitalWrite(pin, HIGH);
}

void SolenoidValve::valveClose() {
  digitalWrite(pin, LOW);
}