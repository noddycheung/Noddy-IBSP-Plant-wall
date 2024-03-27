#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  previousMillis = 0;
}

void UltrasonicSensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int UltrasonicSensor::getDistance() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Transmitting pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Waiting for pulse
    t = pulseIn(echoPin, HIGH);

    // Calculating distance
    h = t * 0.017; 

    h = h - fullTankDistance;  // 5cm
    h = emptyTankDistance - h - fullTankDistance;  // 20cm

    // distance in %, 0-100 %
    total = emptyTankDistance - fullTankDistance;
    hp = h / total * 100;

    // Check for out-of-bounds values
    if (hp > 100) {
      hp = 100;
    } else if (hp < 0) {
      hp = 0;
    }
  }
  return hp;
}

// void UltrasonicSensor::update() {
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;
    
//     // Transmitting pulse
//     digitalWrite(trigPin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trigPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigPin, LOW);

//     // Waiting for pulse
//     t = pulseIn(echoPin, HIGH);

//     // Calculating distance
//     // Serial.print(t);

//     // Calculating distance
//     h = t*0.017; 

//     h = h - fullTankDistance;  //5cm
//     h = emptyTankDistance - h - fullTankDistance;  //20cm

//     // distance in %, 0-100 %
//     total = emptyTankDistance-fullTankDistance;
//     hp = h/total*100;

//     // Sending to computer
//     // Serial.print(h);
//     // Serial.print(" cm");

//     // Checking water level Height in Percentage % (hp)
//     if (hp >= 100) {
//       hp = 100;
//       Serial.print(hp);
//       Serial.print("%");
//       Serial.println("Full");
//     } 
//     else if (hp > 15 && hp < 100) {
//       Serial.print(hp);
//       Serial.print("%");
//       Serial.println("");
//     }
//     else if (hp <= 15 && hp > 0) {
//       Serial.print(hp);
//       Serial.print("%");
//       Serial.println("Almost Empty, need to add water");
//     }
//     else if (hp <= 0) {
//       hp = 0;
//       Serial.print(hp);
//       Serial.print("%");
//       Serial.println("Empty, have to add water");
//     }
//   }
// }