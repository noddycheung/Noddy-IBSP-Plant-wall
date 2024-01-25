#include "msg.h"

void msg::init(HardwareSerial* serial){ 
    nano = serial;

    nano->begin(9600);
}

bool msg::read(){
    if(!nano->available()){ 
        return false;
    }
    if (nano->read() != start_byte){ 
        return false;
    }

    //decoding
    waterLv = (int)nano->read();
    temp = (int)nano->read();
    moist = (int)nano->read();
    PH = (int)nano->read();
    EC = (int)nano->read();
    Nitrogen = (int)nano->read();
    Phosphorus = (int)nano->read();
    Potassium = (int)nano->read();
    flowRate = (int)nano->read();
    isClosePump = (int)nano->read() != 0x00 ? true : false;
    pumpRate = (int)nano->read();
    isCloseValve = (int)nano->read() != 0x00 ? true : false;

    return true;
}

float msg::getWaterLv(){
    return waterLv;
}

float msg::getTemp(){
    return temp;
}
float msg::getMoist(){
    return moist;
}
float msg::getPH(){
    return PH;
}
float msg::getEC(){
    return EC;
}
float msg::getNitrogen(){
    return Nitrogen;
}
float msg::getPhosphorus(){
    return Phosphorus;
}
float msg::getPotassium(){
    return Potassium;
}

float msg::getFlowRate(){
    return flowRate;
}

bool msg::getValveStatus(){
    return isCloseValve;
}
bool msg::getPumpStatus(){
    return isClosePump;
}

float msg::getPumpRate(){
    return pumpRate;
}
