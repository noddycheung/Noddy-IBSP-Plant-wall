#include <Arduino.h>

#ifndef MSG_H
#define MSG_H

    class msg{
        private:
            uint8_t start_byte = 0xff; 
            HardwareSerial* nano;

            float waterLv = 0;
            float temp = 0;
            float moist = 0;
            float PH = 0;
            float EC = 0;
            float Nitrogen = 0;
            float Phosphorus = 0;
            float Potassium = 0;
            bool isCloseValve = 0;
            float flowRate = 0;
            bool isClosePump = 0;
            float pumpRate = 0;

        public:
            void init(HardwareSerial* serial);
            bool read();

            float getWaterLv(); 

            float getTemp();
            float getMoist();
            float getPH();
            float getEC();
            float getNitrogen();
            float getPhosphorus();
            float getPotassium();

            float getFlowRate();
            bool getValveStatus();
            bool getPumpStatus();
            float getPumpRate();
    };

#endif