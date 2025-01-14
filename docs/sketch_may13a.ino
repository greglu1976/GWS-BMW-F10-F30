// Переменные для CAN


uint32_t tmr; // таймер

int INH_P = 4; // приемный вход от ингибитора D4 для положения P
int INH_R = 7; // приемный вход от ингибитора D7 для положения R
int INH_N = 8; // приемный вход от ингибитора D8 для положения N
int INH_D = 9; // приемный вход от ингибитора D9 для положения D

// D5, D6 вместе идут
//Период ШИМ сигнала на портах вход/выхода 5 и 6 будет несколько длиннее. 
//Это связано с тем, что таймер для данных выходов также задействован функциями millis() и delay(). 
//Данный эффект более заметен при установке коротких периодов ШИМ сигнала (0-10).

int MOTOR_P2D = 5; // выход на управление моторчиком D5, от P к D
int MOTOR_D2P = 6; // выход на управление моторчиком D6, от D к P
//analogWrite(MOTOR_OUT, 0xFF) ????? проверить

//Обозначение аналоговых входов начинается буквой «А», от английского слова analog. 
//На плате Arduino Nano эти входы маркируются как A0, A1, A2, A3, A4, A5, A6, A7. 
//Первые пять входов могут использоваться в качестве цифровых, работая в оба направления. 
//Пины A6 и A7 способны работать только на вход!!! 

int DS = A0; // выход на ЭБУ для режима M/S
int PLUS = A1; // выход на ЭБУ М+
int MINUS = A2; // выход на ЭБУ М-

// программные переменные и счетчики
byte inhib_P = 0; 
int count_P = 0; 
byte inhib_R = 0; 
int count_R = 0; 
byte inhib_N = 0;
int count_N = 0; 
byte inhib_D = 0;
int count_D = 0; 


void setup() {
// инициализируем входы от ингибитора
pinMode(INH_P, INPUT);
pinMode(INH_R, INPUT);
pinMode(INH_N, INPUT);  
pinMode(INH_D, INPUT);
// инициализируем выходы на моторчик
pinMode(MOTOR_P2D, OUTPUT);
pinMode(MOTOR_D2P, OUTPUT);
// инициализируем выходы в ЭБУ
pinMode(DS, OUTPUT);
pinMode(PLUS, OUTPUT);
pinMode(MINUS, OUTPUT);

// инициализация CAN шины

//-----------------------
// открываем последовательное соединение для тестирования
Serial.begin(9600);     
//--------------------------------------------------------

// Инициализируем начальное состояние ингибитора
P = digitalRead(INH_P);
if (P){inhib_P = 1;}
R = digitalRead(INH_R);
if (R){inhib_R = 1;}
N = digitalRead(INH_N);
if (N){inhib_N = 1;}
D = digitalRead(INH_D);
if (D){inhib_D = 1;}
//------------------------------------------------

}


void loop() {
  // период 100 мс
  if (millis()-tmr>=100)
  { 
    tmr = millis();
    // читаем состояние ингибитора
    P = digitalRead(INH_P);
    R = digitalRead(INH_R);
    N = digitalRead(INH_N);
    D = digitalRead(INH_D);
    // вывод в serial для отладки

    //-------------------------
    // фиксируем состояние паркинг
    if (P) 
    {
      if (inhib_P!=1)
      { // если состояние ингибитора еще не было установлено в P 
        count_P++;
        if (count_P>5) 
          { // цикл больше 5 раз прошел , значит 500 мс прошло
            inhib_P = 1; // фиксируем паркинг
            count_P = 0; // и сбрасываем счетчик
            inhib_R = 0; // сбрасываем остальные и их счетчики
            count_R = 0; // и сбрасываем счетчик
            inhib_N = 0;
            count_N = 0; // и сбрасываем счетчик
            inhib_D = 0;
            count_D = 0; // и сбрасываем счетчик
          }
      }
     }

 // фиксируем состояние реверс
    if (R) 
    {
      if (inhib_R!=1)
      { // если состояние ингибитора еще не было установлено в R 
        count_R++;
        if (count_R>5) 
          { // цикл больше 5 раз прошел , значит 500 мс прошло
            inhib_P = 0; // 
            count_P = 0; // и сбрасываем счетчик
            inhib_R = 1; // фиксируем реверс
            count_R = 0; // и сбрасываем счетчик
            inhib_N = 0;
            count_N = 0; // и сбрасываем счетчик
            inhib_D = 0;
            count_D = 0; // и сбрасываем счетчик
          }
      }
     }

 // фиксируем состояние нейтраль
    if (N) 
    {
      if (inhib_N!=1)
      { // если состояние ингибитора еще не было установлено в N 
        count_N++;
        if (count_N>5) 
          { // цикл больше 5 раз прошел , значит 500 мс прошло
            inhib_P = 0; // 
            count_P = 0; // и сбрасываем счетчик
            inhib_R = 0; // 
            count_R = 0; // и сбрасываем счетчик
            inhib_N = 1; // фиксируем нейтраль
            count_N = 0; // и сбрасываем счетчик
            inhib_D = 0;
            count_D = 0; // и сбрасываем счетчик
          }
      }
     }

// фиксируем состояние драйв
    if (D) 
    {
      if (inhib_D!=1)
      { // если состояние ингибитора еще не было установлено в D 
        count_D++;
        if (count_D>5) 
          { // цикл больше 5 раз прошел , значит 500 мс прошло
            inhib_P = 0;  
            count_P = 0; // и сбрасываем счетчик
            inhib_R = 0;  
            count_R = 0; // и сбрасываем счетчик
            inhib_N = 0; 
            count_N = 0; // и сбрасываем счетчик
            inhib_D = 1; // фиксируем драйв
            count_D = 0; // и сбрасываем счетчик
          }
      }
     }
    // через 500 мс после пуска на выходе имеем текущее состояние ингибитора
    
  
  } // здесь заканчивается 100 мс цикл
  
// ЗДЕСЬ СЧИТЫВАЕМ С ДЖОЙСТИКА программа борохова

// ---------------------------

}
