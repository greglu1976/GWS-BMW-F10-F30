
//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode
//——————————————————————————————————————————————————————————————————————————————
#include <ACAN2515.h>

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
const uint8_t canMsgEn[5] = {0x05, 0xF0, 0xFC, 0xFF, 0xFF};

const uint8_t canMsgLite[2] = {0xFD, 0x00};

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
//---------------------------------------------------------------

int mot1 = 6; // задаем выход на моторчик, определяется по месту
int mot2 = 5; // задаем выход на моторчик
int inP = 4; // задаем вход от ингибитора P
int inR = 7; // задаем вход от ингибитора R
int inN = 8; // задаем вход от ингибитора N
int inD = 9; // задаем вход от ингибитора D

int DS_minus = 14; // задаем выход на ЭБУ режим M-, A0
int DS_plus = 15; // задаем выход на ЭБУ режим M+, A1
int DS_out = 16; // задаем выход на ЭБУ режим DS, A2
int error_out = 17; // выход на ошибку, A3


//----------------------------------------------------------------------
byte inhibitorP = 0; // задаем переменные контроля положения ингибитора
byte inhibitorR = 0;
byte inhibitorN = 0;
byte inhibitorD = 0;

byte long2self = 0;
byte short2self = 0;
byte longFromSelf = 0;
byte shortFromSelf = 0;
byte pressedP = 0;
byte turnMinus = 0;
byte turnPlus = 0;
byte power = 0;

byte moving = 0 ;
byte moving2R = 0;
byte moving2N = 0;
byte moving2D = 0;
byte moving2P = 0;
byte error = 0;
byte operTime = 0;
byte dsTimer = 0;

uint32_t Timer = 0;
uint32_t tmr = 0;
uint32_t InhibTimer = 0;
int timeDS = 0;

byte timerD = 0;
byte timerR = 0;
byte timerN = 0;
byte timerP = 0;


byte currentSum = 0; // переменные для проверки изменения состояния ингибитора
byte sum = 0;


//---------------------------------------------------------------------


// переменные борохова

byte LongDown = 0;
byte LongUp = 0;
byte ShortDown = 0;
byte ShortUp = 0;
byte D_trans = 0;
byte R_trans = 0;
byte N_trans = 0;
byte DS_trans = 0;
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



void setup()
{
  error = 0; // при сбросе выставляем состояние без ошибок
  moving = 0;
  power = 0xFF; // задаем мощность моторчика 0xFF максимальная

  pinMode(mot1, OUTPUT); // инициализируем первый выход на моторчик (ШИМ)
  pinMode(mot2, OUTPUT); // инициализируем второй выход на моторчик (ШИМ)

  pinMode(inP, INPUT_PULLUP); // инициализируем вход
  pinMode(inR, INPUT_PULLUP); // инициализируем вход
  pinMode(inN, INPUT_PULLUP); // инициализируем вход
  pinMode(inD, INPUT_PULLUP); // инициализируем вход

  pinMode(DS_minus, OUTPUT); // инициализируем выход на ЭБУ
  pinMode(DS_plus, OUTPUT); // инициализируем выход на ЭБУ
  pinMode(DS_out, OUTPUT); // инициализируем выход на ЭБУ
  pinMode(error_out, OUTPUT); // инициализируем выход на ЭБУ

  Serial.begin(9600); // для тестирования

  // считываем текущее положение ингибитора
  if (digitalRead(inP) == LOW) {
    inhibitorP = 1;
  }
  if (digitalRead(inR) == LOW) {
    inhibitorR = 1;
  }
  if (digitalRead(inN) == LOW) {
    inhibitorN = 1;
  }
  if (digitalRead(inD) == LOW) {
    inhibitorD = 1;
  }
  //-----------------------------------------

  //Serial.println("INIT");
  //Serial.println(inhibitorP);
  //Serial.println(inhibitorR);
  //Serial.println(inhibitorN);
  //Serial.println(inhibitorD);

  // от борохова инициализация
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
  // конец инициализации от борохова

}

void loop()
{

  /// подсветка

  CANMessage messageLite;
  messageLite.id = 0x202;
  messageLite.len = 3;
  for (int i = 0; i < 1; i++) {
    messageLite.data[i] = canMsgLite[i];
  }
  ok = can.tryToSend (messageLite) ;



  ///
  /// БЛОК ПЕРЕСЫЛКИ В ДЖОЙСТИК ТЕКУЩЕГО ЗНАЧЕНИЯ ИНГИБИТОРА, выполняется каждые 50 мс
  /// взято у борохова с доработками

  if (gSendDate < millis ()) {



    CANMessage message;
    message.id = 0x3FD;
    message.len = 5;
    if (inhibitorD && !DS_trans) { // если ингибитор в драйве и введен режим DS то посылать не надо D, надо посылать DS
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgD[SendMsgcount][i];
      }
      ok = can.tryToSend (message) ;
    } else if (inhibitorP)
    {
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgP[SendMsgcount][i];
      }
      ok = can.tryToSend (message) ;
    } else if (inhibitorR) {
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgR[SendMsgcount][i];
      }
      ok = can.tryToSend (message) ;
    } else if (inhibitorN) {
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgN[SendMsgcount][i];
        //message.data[0]+=SendMsgDcount*10;
      }
      ok = can.tryToSend (message) ;
    } else if (DS_trans) { // положения DS на ингибиторе и коробке нет, оно виртуальное, отправляем сразу на джойстик
      for (int i = 0; i < 5; i++) {
        message.data[i] = canMsgDS[SendMsgcount][i];
      }
      ok = can.tryToSend (message) ;
    }



    if (ok) {
      //Serial.print (message.id, HEX) ;
      for (int i = 0; i < 5; i++) {
        /*        Serial.print ("  ") ;
                Serial.print (message.data[i], HEX) ;
              }

              Serial.println();
              Serial.print("П=");
              Serial.println(P_trans);
        */
        gSendDate += 50 ; // период выдачи сообщений

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
        gSendDate1000 += 1000 ; // контроль пробуждения ??? проверить должен быть <750 мс
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


  ///
  /// КОНЕЦ БЛОКА ПЕРЕСЫЛКИ В ДЖОЙСТИК ТЕКУЩЕГО ЗНАЧЕНИЯ ИНГИБИТОРА
  ///





  // БЛОК КОДА ДЛЯ ТЕСТА


  if (inhibitorP) {
    //Serial.println("Parking");
  }
  if (digitalRead(inP) == LOW) {
    //Serial.println("READ Parking");
  }
  if (inhibitorR) {
    //Serial.println("Reverse");
  }
  if (digitalRead(inR) == LOW) {
    //Serial.println("READ Reverse");
  }
  if (inhibitorN) {
    //Serial.println("Neutral");
  }
  if (digitalRead(inN) == LOW) {
    //Serial.println("READ Neutral");
  }
  if (inhibitorD) {
    //Serial.println("Drive");
  }
  if (digitalRead(inD) == LOW) {
    //Serial.println("READ Drive");
  }
  // КОНЕЦ БЛОКА КОДА ДЛЯ ТЕСТА

  //
  //БЛОК ПРИЕМА СООБЩЕНИЙ ОТ ДЖОЙСТИКА
  // взято у борохова

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
        long2self = 1;
        short2self = 0;
        longFromSelf = 0;
        shortFromSelf = 0;
        pressedP = 0;
        turnMinus = 0;
        turnPlus = 0;
        DS_trans = 0;
        LongDown = 0;
      }
    }
    else if (frame.data[2] == 0x3E) //Короткое на себя
    {
      ShortDown++;
      if (ShortDown > 8)
      {
        long2self = 0;
        short2self = 1;
        longFromSelf = 0;
        shortFromSelf = 0;
        pressedP = 0;
        turnMinus = 0;
        turnPlus = 0;
        DS_trans = 0;
        ShortDown = 0;
      }
    }
    else if (frame.data[3] == 0xD5)  { // нажата кнопка паркинг
      long2self = 0;
      short2self = 0;
      longFromSelf = 0;
      shortFromSelf = 0;
      pressedP = 1;
      turnMinus = 0;
      turnPlus = 0;
      DS_trans = 0;
    }
    else if (frame.data[2] == 0x2E) //Длинное от себя
    {
      LongUp++;
      if (LongUp > 8) {
        long2self = 0;
        short2self = 0;
        longFromSelf = 1;
        shortFromSelf = 0;
        pressedP = 0;
        turnMinus = 0;
        turnPlus = 0;
        DS_trans = 0;
        LongUp = 0;
      }
    }
    else if (frame.data[2] == 0x1E) //Короткое от себя
    {
      ShortUp++;
      if (ShortUp > 8) {
        long2self = 0;
        short2self = 0;
        longFromSelf = 0;
        shortFromSelf = 1;
        pressedP = 0;
        turnMinus = 0;
        turnPlus = 0;
        DS_trans = 0;
        ShortUp = 0;
      }

    }
    else if (frame.data[2] == 0x7E) //D/S
    {
      //надо включить реле на D/S
      long2self = 0;
      short2self = 0;
      longFromSelf = 0;
      shortFromSelf = 0;
      pressedP = 0;
      turnMinus = 0;
      turnPlus = 0;
      DS_trans = 1;
    }
    else if (frame.data[2] == 0x5E) //D/S-
    {
      turnMinus = 1;
      turnPlus = 0;

    }
    else if (frame.data[2] == 0x6E) //D/S+
    {
      //надо включить реле +
      turnMinus = 0;
      turnPlus = 1;
    }
    else if (frame.data[2] == 0x0E) // если джойстик выдает 0E значит он в нейтральном положении, в положении DS он постоянно выдает 7E
    {
      // по этому факту сбрасываем состояние DS
      DS_trans = 0;
      // если нет сообщений, то обнуляем все переменные, кроме DS_trans
      long2self = 0;
      short2self = 0;
      longFromSelf = 0;
      shortFromSelf = 0;
      pressedP = 0;
      turnMinus = 0;
      turnPlus = 0;
    }
  }

  // если моторчик в движении, то игнорируем все сообщения от джойстика
  // здесь можно добавить проверку на ошибки


  if (moving == 1) {
    //Serial.println("OK"); // для теста
    long2self = 0;
    short2self = 0;
    longFromSelf = 0;
    shortFromSelf = 0;
    pressedP = 0;
    turnMinus = 0;
    turnPlus = 0;
  }

  //
  //КОНЕЦ БЛОКА ПРИЕМА СООБЩЕНИЙ ОТ ДЖОЙСТИКА
  // на выходе имеем переменную с выбранным нажатием джойстика, всего 8 режимов
  //


  //
  // БЛОК РЕАЛИЗАЦИИ ВЫБРАННЫХ РЕЖИМОВ
  //

  if (long2self) {
    analogWrite(mot1, power); // запускаем моторчик прямо, т.е. от P->D
    moving = 1; // выставляем флаг работы моторчика
    moving2D = 1; // выставляем флаг работы моторчика до положения D
  }
  if (short2self) {
    if (inhibitorP) {
      analogWrite(mot1, power); // запускаем моторчик прямо, т.е. от P->D
      moving = 1; // выставляем флаг работы моторчика
      moving2R = 1; // выставляем флаг работы моторчика до положения R
    }
    if (inhibitorR) {
      analogWrite(mot1, power); // запускаем моторчик прямо, т.е. от P->D
      moving = 1; // выставляем флаг работы моторчика
      moving2N = 1; // выставляем флаг работы моторчика до положения N
    }
    if (inhibitorN) {
      analogWrite(mot1, power); // запускаем моторчик прямо, т.е. от P->D
      moving = 1; // выставляем флаг работы моторчика
      moving2D = 1; // выставляем флаг работы моторчика до положения D
    }
  }

  if (longFromSelf && inhibitorD) {
    analogWrite(mot2, power); // запускаем моторчик обратно, т.е. от D->P
    moving = 1; // выставляем флаг работы моторчика
    moving2R = 1; // выставляем флаг работы моторчика до положения R
  }
  if (shortFromSelf) {
    if (inhibitorD) {
      analogWrite(mot2, power); // запускаем моторчик обратно, т.е. от D->P
      moving = 1; // выставляем флаг работы моторчика
      moving2N = 1; // выставляем флаг работы моторчика до положения N
    }
    if (inhibitorN) {
      analogWrite(mot2, power); // запускаем моторчик обратно, т.е. от D->P
      moving = 1; // выставляем флаг работы моторчика
      moving2R = 1; // выставляем флаг работы моторчика до положения R
    }
  }

  if (pressedP && !inhibitorP) { // если кнопка нажата и коробка не в паркинге, чтобы лишний раз моторчик не дергать
    analogWrite(mot2, power); // запускаем моторчик обратно, т.е. от D->P
    moving = 1; // выставляем флаг работы моторчика
    moving2P = 1; // выставляем флаг работы моторчика до положения P

  }

  if (DS_trans) { // выбран режим DS
    digitalWrite(DS_out, HIGH);
    //Serial.print ("DS activated") ;
  } else {
    // возврат DS
    digitalWrite(DS_out, LOW);
    //Serial.print ("DS DEactivated") ;
  }

  if (DS_trans && turnMinus) {
    dsTimer = 1; // запускаем таймер
    digitalWrite(DS_minus, HIGH);
    //Serial.print ("DS MINUS activated") ;
  }

  if (DS_trans && turnPlus) {
    dsTimer = 1; // запускаем таймер
    digitalWrite(DS_plus, HIGH);
    //Serial.print ("DS PLUS activated") ;
  }

  if (dsTimer) {
    if (millis() - Timer >= 50) {
      Timer = millis();
      timeDS = timeDS + 50;
      if (timeDS >= 300) { // длительность импульса в ЭБУ на М+ М- здесь 300 мс, выставляется по месту
        digitalWrite(DS_minus, LOW); // снимаем сигнал M-
        digitalWrite(DS_plus, LOW); // снимаем сигнал M+
        timeDS = 0; // обнуляем выдержку
        dsTimer = 0; // останавливаем таймер
      }
    }
  }

  //
  // КОНЕЦ БЛОКА РЕАЛИЗАЦИИ ВЫБРАННЫХ РЕЖИМОВ
  //



  //
  // БЛОК КОНТРОЛЯ РАБОТЫ МОТОРЧИКА
  // Контролируем движение моторчика и время его работы (если больше 5 секунд то останавливаем, время настраивается по месту)
  if (millis() - tmr >= 100) {
    tmr = millis();
    if (moving == 1) {
      operTime = operTime + 1;
      if (operTime >= 50) {
        analogWrite(mot1, 0); // обнуляем выхода ардуино
        analogWrite(mot2, 0); // для останова моторчика
        moving = 0 ; // снимаем флаги движения
        moving2R = 0;
        moving2N = 0;
        moving2D = 0;
        moving2P = 0;
        error = 1; // выставляем ошибку превышение времени работы моторчика, обнуляется рестартом платы ардуино
        operTime = 0;
      }
    }
    else {
      operTime = 0;
    }
  }

  if (moving2R == 1 && inhibitorR == 1 ) { // если достигли R то останавливаем моторчик
    analogWrite(mot1, 0); // обнуляем выхода ардуино
    analogWrite(mot2, 0); // обнуляем выхода ардуино
    moving2R = 0; // сбрасываем флаг движения к R
    moving = 0; // сбрасываем общий флаг движения
  }
  if (moving2P == 1 && inhibitorP == 1 ) { // если достигли P то останавливаем моторчик
    analogWrite(mot1, 0);
    analogWrite(mot2, 0);
    moving2P = 0;
    moving = 0;
  }
  if (moving2N == 1 && inhibitorN == 1 ) { // если достигли N то останавливаем моторчик
    analogWrite(mot1, 0);
    analogWrite(mot2, 0);
    moving2N = 0;
    moving = 0;
  }
  if (moving2D == 1 && inhibitorD == 1 ) { // если достигли D то останавливаем моторчик
    analogWrite(mot1, 0);
    analogWrite(mot2, 0);
    moving2D = 0;
    moving = 0;
  }
  /// КОНЕЦ БЛОКА КОНТРОЛЯ МОТОРЧИКА




  ///
  /// БЛОК СЧИТЫВАНИЯ ПОЛОЖЕНИЯ ИНГИБИТОРА
  ///

  if (millis() - InhibTimer >= 1) {
    InhibTimer = millis();

    if (digitalRead(inP) == LOW) {
      timerP = timerP + 1;
      timerR = 0;
      timerN = 0;
      timerD = 0;
      if (timerP > 10) {
        inhibitorP = 1; // через 10 мс выставляем P, время по месту регулируется
        inhibitorR = 0; // остальные сбрасываем
        inhibitorN = 0;
        inhibitorD = 0;
      }
    }
    if (digitalRead(inR) == LOW) {
      timerR = timerR + 1;
      timerP = 0;
      timerN = 0;
      timerD = 0;
      if (timerR > 10) {
        inhibitorP = 0; // через 10 мс выставляем R
        inhibitorR = 1; // остальные сбрасываем
        inhibitorN = 0;
        inhibitorD = 0;
        timerR = 0;
      }
    }
    if (digitalRead(inN) == LOW) {
      timerN = timerN + 1;
      timerR = 0;
      timerP = 0;
      timerD = 0;
      if (timerN > 10) {
        inhibitorP = 0; // через 10 мс выставляем N
        inhibitorR = 0; // остальные сбрасываем
        inhibitorN = 1;
        inhibitorD = 0;
        timerN = 0;
      }
    }

    if (digitalRead(inD) == LOW) {
      timerD = timerD + 1;
      timerR = 0;
      timerN = 0;
      timerP = 0;
      if (timerD > 10) {
        inhibitorP = 0; // через 10 мс выставляем D
        inhibitorR = 0; // остальные сбрасываем
        inhibitorN = 0;
        inhibitorD = 1;
        timerD = 0;
      }
    }
  }

  // БЛОК ФИКСАЦИИ ОШИБКИ
  // сейчас по превышению времени работы моторчика, можно добавить по отсутствию сигналов от ингибитора
  //

  if (error) 
  {
     digitalWrite(error_out, HIGH); // выдаем на выход
  }
  else {
    digitalWrite(error_out, LOW); // снимаем с выхода
  }
  // КОНЕЦ БЛОКА ФИКСАЦИИ ОШИБКИ
}
