#include "sounds.h"

String incomingString = "";
int melody[] = { 
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int blueLed = 11;           
int greenLed = 10; 
int redLed = 9; 
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int PinOut[4] {4, 13, 2, 12};
int PinIn[4] {8, 7, 6, 5};
int val = 0;
const char value[4][4]
{ {'1', '4', '7', '*'},
  {'2', '5', '8', '0' },
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
// двойной массив, обозначающий кнопку
 
int b = 0; // переменная, куда кладется число из массива(номер кнопки)

void setup() { 
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  pinMode (12, OUTPUT); // инициализируем порты на выход (подают нули на столбцы)
  pinMode (2, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (4, OUTPUT);
 
  pinMode (5, INPUT); // инициализируем порты на вход с подтяжкой к плюсу (принимают нули на строках)
  digitalWrite(5, HIGH);
  pinMode (6, INPUT);
  digitalWrite(6, HIGH);
  pinMode (7, INPUT);
  digitalWrite(7, HIGH);
  pinMode (8, INPUT);
  digitalWrite(8, HIGH);
  
  Serial.begin(9600);  
};



void playMelody(){
   for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(3, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
}
}

void matrix (){ // создаем функцию для чтения кнопок
  for (int i = 1; i <= 4; i++) // цикл, передающий 0 по всем столбцам
  {
    digitalWrite(PinOut[i - 1], LOW); // если i меньше 4 , то отправляем 0 на ножку
    for (int j = 1; j <= 4; j++) // цикл, принимающих 0 по строкам
    {
      if (digitalRead(PinIn[j - 1]) == LOW) // если один из указанных портов входа равен 0, то..
      {
        Serial.println( value[i - 1][j - 1]); // то b равно значению из двойного массива
        delay(175);
      }
    }
    digitalWrite(PinOut[i - 1], HIGH); // подаём обратно высокий уровень
  }
}

void loop(){     
  if (Serial.available() > 0){
      incomingString = Serial.readString();
     }  
  matrix ();     
  if(incomingString == "on"){   
    analogWrite(blueLed, brightness);
    delay(80);
    analogWrite(redLed, brightness);
    delay(80);
    brightness = brightness + fadeAmount;
   }  
  if(incomingString == "off"){
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, LOW);
   }
  if(incomingString == "bip on"){
    playMelody();
  }   
  if(incomingString == "bip off"){ 
    noTone(3);
  }   
  delay(1);
} 

   


