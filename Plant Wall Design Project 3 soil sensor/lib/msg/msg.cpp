// #include "msg.h"

// void msg::init(HardwareSerial* serial){ 
//     serial = serial_;

//     serial_->begin(9600);
//     unsigned char encryptkey[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// }

// void msg::msg_send() {
//     if (Serial.available())
//   {
//       char data[8];
//     //     printrecvBuffer(buf, len);
//     //     myprintBuffer("Received: ", buf, len);
//         // data[0] = 0x01; //packet type is ack
//         // data[1] = getflowRate();
//         // data[2] = buf[4];
//         // data[3] = STATIONID_HIGHBYTE; //Transmitting/Source Station ID highByte
//         // data[4] = STATIONID_LOWBYTE; //Transmitting/Source Station ID lowByte
//         // data[5] = buf[5];
//         // data[6] = buf[6];
//         // data[7] = 0x00;
//         //Serial.println(data);
//         serial_->write(data, sizeof(data));
//       }
//     else
//     {
//       Serial.println("Receive failed");
//     }
// }



// void printrecvBuffer(const uint8_t* buf, uint8_t len)
// {
//   uint8_t i;
//   for (i = 0; i < len; i++)
//   {
//     Serial.write(buf[i]);
//   }
// }


// void myprintBuffer(const char* prompt, const uint8_t* buf, uint8_t len)
// {
//   uint8_t i;
//   Serial1.println(prompt);
//   for (i = 0; i < len; i++)
//   {
//     Serial1.print(buf[i], HEX);
//     Serial1.print(' ');
//   }
//   Serial1.println("");
// }