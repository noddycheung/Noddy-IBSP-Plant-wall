#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(uint8_t rxPin, uint8_t txPin) : ss(rxPin, txPin) {}

void UltrasonicSensor::begin() {
  ss.begin(9600);
}

float UltrasonicSensor::readDistance() {
  byte hdr, data_h, data_l, chksum;
  unsigned int distance = 0;
  ss.print(0x00);
  hdr = ss.read();
  if (hdr == 255) {
    data_h = ss.read();
    data_l = ss.read();
    chksum = ss.read();
    if (chksum == ((hdr + data_h + data_l) & 0x00FF)) {
      distance = data_h * 256 + data_l;
    }
  }
  float hp = constrain(map(distance,140,0,0,100),0,100);

  return hp;
}
