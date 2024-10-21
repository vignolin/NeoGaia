/*
 
 ^` CODE WRITTEN BY VIGNOLIN - IF COPYING, PLEASE MAINTAIN THIS SECTION.
*/

//------- LIBRARIES ----------//

#include <virtuabotixRTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>


// ------ VARIABLES, CONSTANTS AND ARRAYS ------- //

const short reservatorioCheio = 2;
const  short reservatorioMeio = 3;
const short reservatorioVazio = 4;

const short sensorUmidade = 7; 

const short dataPin = 8; // Shift Register 74hc595n
const short clockPin = 9; // Shift Register 74hc595n
const short latchPin = 10; // Shift Register 74hc595n
 byte com0; // Shift Register 74hc595n

 



short niveis = 2;
short outputs = 1;
 const short inputs[] = {reservatorioCheio, reservatorioMeio, reservatorioVazio};
 const short output[] = { dataPin, clockPin, latchPin};
 


 const short clk = 10; // RTC DS1302
 const short dat = 11; // RTC DS1302
 const short rst = 12; // RTC DS1302


 /* Protocolo para o 74hc595:
   - Pinos: 
     D1 = bomba d'água;
     D2 = energia no reservatório; 
     D3 = sensor de Umidade;
 */

// --------- OBJECTS ----------- //

virtuabotixRTC   myRTC(clk, dat, rst);    
LiquidCrystal_I2C lcd(0x27,20,4);

//--------- FUNÇÕES ------------

void updateShiftRegister(){
  digitalWrite(latchPin, LOW);
  ShiftOut(dataPin, clockPin, MSBFIRST, com0);
  digitalWrite(latchPin, HIGH);
}
void onCommand(){
  com0 = B00000010;
  updateShiftRegister();
  Serial.print(" Status: ");

  int nivelArray[] =  {
    digitalRead(inputs[0]),
    digitalRead(inputs[1]), 
    digitalRead(inputs[2])
    };

  unsigned int bit;

  if(nivelArray[0] != 1 && nivelArray[1] == 1){
    int bit = "60%";
  } else if(nivelArray[2] != 0 && nivelArray[1] == 0){
    int bit = "40%";
  } else if(nivelArray[2] == 0){
    int bit = "20%";
  } else if(nivelArray[0] == 1){
    int bit = "80%";
  }
  Serial.print(bit);
  lcd.backlight();     
  lcd.setCursor(0,2);
  lcd.print("RESERVATORIO EM:");
  lcd.setCursor(1, 7);
  lcd.print(bit);
  
  com0 = B00000000;
  updateShiftRegister();
  
}
 


//-------- FUNÇÕES PRINCIPAIS -------------


void setup(){
  Serial.begin(9600);
// ajustar pinos i/o;
  for(short pinos = 0; pinos<inputs; pinos++){
  pinMode(inputs[pinos], INPUT);
  Serial.print("Nível ");
  Serial.print(pinos);
  Serial.println(" ajustado corretamente");
  }
  for(short pinosout = 0; pinosout<outputs; pinosout++){
    pinMode(output[pinosout], OUTPUT);
    Serial.println("Pinos Output:");
    Serial.print(pinosout);
    Serial.println("Ajustado!");
  }
} 


void loop(){
unsigned long tempoAnterior = 0;
const long intervalo = 3600000; // 1 hora
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    onCommand();
  }
  delay(1000);
}