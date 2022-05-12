//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections:
//    - standard SPI pins for SCK, MOSI and MISO
//    - a digital output for CS
//    - interrupt input pin for INT
//——————————————————————————————————————————————————————————————————————————————
// If you use CAN-BUS shield (http://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/) with Arduino Uno,
// use B connections for MISO, MOSI, SCK, #9 or #10 for CS (as you want),
// #2 or #3 for INT (as you want).
//——————————————————————————————————————————————————————————————————————————————

static const byte MCP2515_CS  = 10 ; // CS input of MCP2515 (adapt to your design)
static const byte MCP2515_INT =  2 ; // INT output of MCP2515 (adapt to your design)
const uint8_t canMsgP[15][5] = {
  {0xF3, 0x00, 0x20, 0x0C, 0xFF},
  {0x6E, 0x01, 0x20, 0x0C, 0xFF},
  {0xD4, 0x02, 0x20, 0x0C, 0xFF},
  {0x49, 0x03, 0x20, 0x0C, 0xFF},
  {0xBD, 0x04, 0x20, 0x0C, 0xFF},
  {0x20, 0x05, 0x20, 0x0C, 0xFF},
  {0x9A, 0x06, 0x20, 0x0C, 0xFF},
  {0x07, 0x07, 0x20, 0x0C, 0xFF},
  {0x6F, 0x08, 0x20, 0x0C, 0xFF},
  {0xF2, 0x09, 0x20, 0x0C, 0xFF},
  {0x48, 0x0A, 0x20, 0x0C, 0xFF},
  {0xD5, 0x0B, 0x20, 0x0C, 0xFF},
  {0x21, 0x0C, 0x20, 0x0C, 0xFF},
  {0xBC, 0x0D, 0x20, 0x0C, 0xFF},
  {0x06, 0x0E, 0x20, 0x0C, 0xFF},
};
/*
  11  00  20  FC  FF
  8C  01  20  FC  FF
  36  02  20  FC  FF
  AB  03  20  FC  FF
  5F  04  20  FC  FF
  C2  05  20  FC  FF
  78  06  20  FC  FF
  E5  07  20  FC  FF
  8D  08  20  FC  FF
  10  09  20  FC  FF
  AA  0A  20  FC  FF
  37  0B  20  FC  FF
  C3  0C  20  FC  FF
  5E  0D  20  FC  FF
  E4  0E  20  FC  FF

*/
const uint8_t canMsgEn[5] = {0x05, 0xF0, 0xFC, 0xFF, 0xFF};
const uint8_t canMsgSP[15][7] = {
  {0x1A1, 5, 0xFC, 0xC6, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x61, 0xC7, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x09, 0xC8, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x94, 0xC9, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x2E, 0xCA, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0xB3, 0xCB, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x47, 0xCC, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0xDA, 0xCD, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x60, 0xCE, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x95, 0xC0, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x08, 0xC1, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0xB2, 0xC2, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x2F, 0xC3, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0xDB, 0xC4, 0x00, 0x00, 0x81},
  {0x1A1, 5, 0x46, 0xC5, 0x00, 0x00, 0x81},
};


const uint8_t canMsgD[15][5] = {
  {0x03, 0x00, 0x80, 0x0C, 0xFF},
  {0x9E, 0x01, 0x80, 0x0C, 0xFF},
  {0x24, 0x02, 0x80, 0x0C, 0xFF},
  {0xB9, 0x03, 0x80, 0x0C, 0xFF},
  {0x4D, 0x04, 0x80, 0x0C, 0xFF},
  {0xD0, 0x05, 0x80, 0x0C, 0xFF},
  {0x6A, 0x06, 0x80, 0x0C, 0xFF},
  {0xF7, 0x07, 0x80, 0x0C, 0xFF},
  {0x9F, 0x08, 0x80, 0x0C, 0xFF},
  {0x02, 0x09, 0x80, 0x0C, 0xFF},
  {0xB8, 0x0A, 0x80, 0x0C, 0xFF},
  {0x25, 0x0B, 0x80, 0x0C, 0xFF},
  {0xD1, 0x0C, 0x80, 0x0C, 0xFF},
  {0x4C, 0x0D, 0x80, 0x0C, 0xFF},
  {0xF6, 0x0E, 0x80, 0x0C, 0xFF}
};
const uint8_t canMsgDS[15][5] = {
  {0xA9, 0x10, 0x81, 0x0C, 0xFF},
  {0x34, 0x11, 0x81, 0x0C, 0xFF},
  {0x8E, 0x12, 0x81, 0x0C, 0xFF},
  {0x13, 0x13, 0x81, 0x0C, 0xFF},
  {0xE7, 0x14, 0x81, 0x0C, 0xFF},
  {0x7A, 0x15, 0x81, 0x0C, 0xFF},
  {0xC0, 0x16, 0x81, 0x0C, 0xFF},
  {0x5D, 0x17, 0x81, 0x0C, 0xFF},
  {0x35, 0x18, 0x81, 0x0C, 0xFF},
  {0xA8, 0x19, 0x81, 0x0C, 0xFF},
  {0x12, 0x1A, 0x81, 0x0C, 0xFF},
  {0x8F, 0x1B, 0x81, 0x0C, 0xFF},
  {0x7B, 0x1C, 0x81, 0x0C, 0xFF},
  {0xE6, 0x1D, 0x81, 0x0C, 0xFF},
  {0x5C, 0x1E, 0x81, 0x0C, 0xFF}
};
/*
   A9 10 81 0C FF
  3FD, 00, 5, 34 11 81 0C FF
  3FD, 00, 5, 8E 12 81 0C FF
  3FD, 00, 5, 13 13 81 0C FF
  3FD, 00, 5, E7 14 81 0C FF
  3FD, 00, 5, 7A 15 81 0C FF
  3FD, 00, 5, C0 16 81 0C FF
  3FD, 00, 5, 5D 17 81 0C FF
  3FD, 00, 5, 35 18 81 0C FF
  3FD, 00, 5, A8 19 81 0C FF
  3FD, 00, 5, 12 1A 81 0C FF
  3FD, 00, 5, 8F 1B 81 0C FF
  3FD, 00, 5, 7B 1C 81 0C FF
  3FD, 00, 5, E6 1D 81 0C FF
  3FD, 00, 5, 5C 1E 81 0C FF
*/
const uint8_t canMsgN[15][5] = {
  {0x93, 0x00, 0x60, 0x0C, 0xFF},
  {0x0E, 0x01, 0x60, 0x0C, 0xFF},
  {0xB4, 0x02, 0x60, 0x0C, 0xFF},
  {0x29, 0x03, 0x60, 0x0C, 0xFF},
  {0xDD, 0x04, 0x60, 0x0C, 0xFF},
  {0x40, 0x05, 0x60, 0x0C, 0xFF},
  {0xFA, 0x06, 0x60, 0x0C, 0xFF},
  {0x67, 0x07, 0x60, 0x0C, 0xFF},
  {0x0F, 0x08, 0x60, 0x0C, 0xFF},
  {0x92, 0x09, 0x60, 0x0C, 0xFF},
  {0x28, 0x0A, 0x60, 0x0C, 0xFF},
  {0xB5, 0x0B, 0x60, 0x0C, 0xFF},
  {0x41, 0x0C, 0x60, 0x0C, 0xFF},
  {0xDC, 0x0D, 0x60, 0x0C, 0xFF},
  {0x66, 0x0E, 0x60, 0x0C, 0xFF}
};
/*

   3FD, 00, 5, 93 00 60 0C FF
  3FD, 00, 5, 0E 01 60 0C FF
  3FD, 00, 5, B4 02 60 0C FF
  3FD, 00, 5, 29 03 60 0C FF
  3FD, 00, 5, DD 04 60 0C FF
  3FD, 00, 5, 40 05 60 0C FF
  3FD, 00, 5, FA 06 60 0C FF
  3FD, 00, 5, 67 07 60 0C FF
  3FD, 00, 5, 0F 08 60 0C FF
  3FD, 00, 5, 92 09 60 0C FF
  3FD, 00, 5, 28 0A 60 0C FF
  3FD, 00, 5, B5 0B 60 0C FF
  3FD, 00, 5, 41 0C 60 0C FF
  3FD, 00, 5, DC 0D 60 0C FF
  3FD, 00, 5, 66 0E 60 0C FF

   0F 08 60 0C FF


  3FD, 00, 5, 92 09 60 0C FF
  3FD, 00, 5, 28 0A 60 0C FF
  3FD, 00, 5, B5 0B 60 0C FF


*/
/*
  3FD, 00, 5, C3 00 00 0C FF
  3FD, 00, 5, 5E 01 00 0C FF
  3FD, 00, 5, E4 02 00 0C FF
  3FD, 00, 5, 79 03 00 0C FF
  3FD, 00, 5, 8D 04 00 0C FF
  3FD, 00, 5, 10 05 00 0C FF
  3FD, 00, 5, AA 06 00 0C FF
  3FD, 00, 5, 37 07 00 0C FF
  3FD, 00, 5, 5F 08 00 0C FF
  3FD, 00, 5, C2 09 00 0C FF
  3FD, 00, 5, 78 0A 00 0C FF
  3FD, 00, 5, E5 0B 00 0C FF
  3FD, 00, 5, 11 0C 00 0C FF
  3FD, 00, 5, 8C 0D 00 0C FF
  3FD, 00, 5, 36 0E 00 0C FF
*/
const uint8_t canMsg00[15][5] = {
  {0xC3, 0x00, 0x00, 0x0C, 0xFF},
  {0x5E, 0x01, 0x00, 0x0C, 0xFF},
  {0xE4, 0x02, 0x00, 0x0C, 0xFF},
  {0x79, 0x03, 0x00, 0x0C, 0xFF},
  {0x8D, 0x04, 0x00, 0x0C, 0xFF},
  {0x10, 0x05, 0x00, 0x0C, 0xFF},
  {0xAA, 0x06, 0x00, 0x0C, 0xFF},
  {0x37, 0x07, 0x00, 0x0C, 0xFF},
  {0x5F, 0x08, 0x00, 0x0C, 0xFF},
  {0xC2, 0x09, 0x00, 0x0C, 0xFF},
  {0x78, 0x0A, 0x00, 0x0C, 0xFF},
  {0xE5, 0x0B, 0x00, 0x0C, 0xFF},
  {0x11, 0x0C, 0x00, 0x0C, 0xFF},
  {0x8C, 0x0D, 0x00, 0x0C, 0xFF},
  {0x36, 0x0E, 0x00, 0x0C, 0xFF}
};
const uint8_t canMsgR[15][5] = {
  {0xA3, 0x00, 0x40, 0x0C, 0xFF},
  {0x3E, 0x01, 0x40, 0x0C, 0xFF},
  {0x84, 0x02, 0x40, 0x0C, 0xFF},
  {0x19, 0x03, 0x40, 0x0C, 0xFF},
  {0xED, 0x04, 0x40, 0x0C, 0xFF},
  {0x70, 0x05, 0x40, 0x0C, 0xFF},
  {0xCA, 0x06, 0x40, 0x0C, 0xFF},
  {0x57, 0x07, 0x40, 0x0C, 0xFF},
  {0x3F, 0x08, 0x40, 0x0C, 0xFF},
  {0xA2, 0x09, 0x40, 0x0C, 0xFF},
  {0x18, 0x0A, 0x40, 0x0C, 0xFF},
  {0x85, 0x0B, 0x40, 0x0C, 0xFF},
  {0x71, 0x0C, 0x40, 0x0C, 0xFF},
  {0xEC, 0x0D, 0x40, 0x0C, 0xFF},
  {0x56, 0x0E, 0x40, 0x0C, 0xFF}
};
/*
  20 F 6 D 4 B 2 9 0 6 F 4 D 2 B 0
  40 A 3 8 1 E 7 C 5 3 A 1 8 7 E 5
  60 5 C         3 A C 5         A
  80 0 9 2 B 4 D 6 F 9 0 B 2 D 4 F
  5  C 7 e 1 8 3 A 5 e 7 e 8 1 A

*/
byte LongDown = 0;
byte LongUp = 0;
byte ShortDown = 0;
byte ShortUp = 0;
byte D_trans = 0;
byte R_trans = 0;
byte N_trans = 0;
byte DS_trans = 0;
boolean KeyP = false;
unsigned long gSendDate, gSendDate1000, gSendDate200;
byte SendMsgSPcount = 0;
byte SendMsgcount = 0;
byte SendMsgDcount = 0;
byte P_trans = 0; //будем считать что мы на парковке;
bool ok = 0;
byte n = 0;

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2515 can (MCP2515_CS, SPI, MCP2515_INT) ;

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Quartz: adapt to your design
//——————————————————————————————————————————————————————————————————————————————

static const uint32_t QUARTZ_FREQUENCY = 8UL * 1000UL * 1000UL ; // 16 MHz

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void setup () {

  //--- Start serial
  //  Serial.begin (115200) ;
  //--- Wait for serial (blink led at 10 Hz during waiting)
//  while (!Serial) {
//    delay (50) ;
//  }
  //--- Begin SPI
  SPI.begin () ;
  //--- Configure ACAN2515
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 500UL * 1000UL) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::NormalMode ; // Select loopback mode
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;


  while (SendMsgcount > 14)
  {
    CANMessage message;
    message.id = 0x3FD;
    message.len = 5;
    for (int i = 0; i < 5; i++) {
      message.data[i] = canMsg00[SendMsgcount][i];
    }
    if (gSendDate < millis ()) {
      ok = can.tryToSend (message) ;
      if (ok) {
        gSendDate += 100 ;
        SendMsgcount++;
      }
    }
  }
  P_trans = 1;
}

//----------------------------------------------------------------------------------------------------------------------

//static uint32_t gBlinkLedDate = 0 ;
//static uint32_t gReceivedFrameCount = 0 ;
//static uint32_t gSentFrameCount = 0 ;

//——————————————————————————————————————————————————————————————————————————————


void loop () {
  CANMessage frame ;
  //unsigned long currentMillis = millis();

  // Если стоит на паркинге, светим паркинг.
  if (can.available ()) {
    can.receive (frame) ;
    if (frame.id == 0x197)
      Serial.print (frame.id, HEX) ;
    for (int i = 0; i < 5; i++) {
      Serial.print ("  ") ;
      Serial.print (frame.data[i], HEX) ;
    }
    Serial.println();
      if (frame.data[2] == 0x4E) //Длинное на себя
      {
        LongDown++;
        if (LongDown > 8)
        {
          D_trans = 1;
          P_trans = 0;
          R_trans = 0;
          DS_trans = 0;
          LongDown = 0;
        }
      } else if (frame.data[2] == 0x3E) //Короткое на себя
      {
        ShortDown++;
        if (ShortDown > 8)
        {
          if (P_trans) {
            D_trans = 1;
            P_trans = 0;
            R_trans = 0;
            DS_trans = 0;
          } else if (R_trans) {
            N_trans = 1;
            R_trans = 0;
            DS_trans = 0;
          } else if (N_trans) {
            D_trans = 1;
            P_trans = 0;
            R_trans = 0;
            N_trans = 0;
            DS_trans = 0;
          }
          ShortDown = 0;
        }
      } else if (frame.data[3] == 0xD5)  {
        D_trans = 0;
        P_trans = 1;
        R_trans = 0;
        N_trans = 0;
        DS_trans = 0;
      } else if (frame.data[2] == 0x2E) //Длинное от себя
      {
        LongUp++;
        if (LongUp > 8) {
          D_trans = 0;
          P_trans = 0;
          R_trans = 1;
          DS_trans = 0;
          LongUp = 0;
        }
      } else if (frame.data[2] == 0x1E) //Короткое от себя
      {
        ShortUp++;
        if (ShortUp > 8) {
          if (D_trans) {
            D_trans = 0;
            P_trans = 0;
            R_trans = 0;
            N_trans = 1;
            DS_trans = 0;
          } else if (N_trans) {
            D_trans = 0;
            P_trans = 0;
            R_trans = 1;
            N_trans = 0;
            DS_trans = 0;

          }
          ShortUp = 0;
        }
      } else if (frame.data[2] == 0x7E && !P_trans) //D/S
      {
        //надо включить реле на D/S
        D_trans = 0;
        P_trans = 0;
        R_trans = 0;
        N_trans = 0;
        DS_trans = 1;
      }else if (frame.data[2] == 0x5E) //D/S-
      {
        //надо включить реле -

      }else if (frame.data[2] == 0x6E) //D/S+
      {
        //надо включить реле +

      }

    }
    if (gSendDate < millis ()) {
      CANMessage message, message1;
      message.id = 0x3FD;
      message.len = 5;
      if (D_trans) {
        for (int i = 0; i < 5; i++) {
          message.data[i] = canMsgD[SendMsgcount][i];
        }
        ok = can.tryToSend (message) ;
      } else if (P_trans)
      {
        for (int i = 0; i < 5; i++) {
          message.data[i] = canMsgP[SendMsgcount][i];
        }
        ok = can.tryToSend (message) ;
      } else if (R_trans) {
        for (int i = 0; i < 5; i++) {
          message.data[i] = canMsgR[SendMsgcount][i];
        }
        ok = can.tryToSend (message) ;
      } else if (N_trans) {
        for (int i = 0; i < 5; i++) {
          message.data[i] = canMsgN[SendMsgcount][i];
          //message.data[0]+=SendMsgDcount*10;
        }
      } else if (DS_trans) {
        for (int i = 0; i < 5; i++) {
          message.data[i] = canMsgDS[SendMsgcount][i];
        }
        ok = can.tryToSend (message) ;
      }

      if (ok) {
        Serial.print (message.id, HEX) ;
        for (int i = 0; i < 5; i++) {
  /*        Serial.print ("  ") ;
          Serial.print (message.data[i], HEX) ;
        }

        Serial.println();
        Serial.print("П=");
        Serial.println(P_trans);
        */
        gSendDate += 200 ;

        SendMsgcount++;
        if (SendMsgcount > 14) SendMsgcount = 0;
      }
    } else if (gSendDate1000 < millis()) {
      CANMessage message;
      message.id = 0x130;
      message.len = 5;
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgEn[i];
      }
      ok = can.tryToSend (message) ;
      if (ok) {
        gSendDate1000 += 1000 ;
      }
    } else if (gSendDate200 < millis()) {
      CANMessage message;
      message.id = 0xA1A;
      message.len = 5;
      for (int i = 2; i < 7; i++) {
        message.data[i] = canMsgSP[SendMsgSPcount][i];
      }
      ok = can.tryToSend (message) ;
      if (ok) {
        gSendDate200 += 200 ;
      }
      SendMsgSPcount++;
      if (SendMsgSPcount > 14) SendMsgSPcount = 0;
    }

  }
}


  //——————————————————————————————————————————————————————————————————————————————
