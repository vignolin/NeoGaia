//------- LIBRARIES ----------//

#include <virtuabotixRTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>


// ------ VARIABLES, CONSTANTS AND ARRAYS ------- //


 short reservatorioCheio = 2;
 short reservatorioMeio = 3;
 short reservatorioVazio = 4;
 short reservatorioSensor = 6;

 short sensorPower = 7;
 short sensorMoisture = 8; 
 short relay = 9;


 const short niveis = 3;
 const short outputs = 2;

 const short nivelAgua[] = {reservatorioCheio, reservatorioMeio, reservatorioVazio,};
 const short output[] = {relay, reservatorioSensor};
 const short input[] = { 10, 11, 12};


 const short clk = 10;
 const short dat = 11;
 const short rst = 12;



// --------- OBJECTS ----------- //

virtuabotixRTC   myRTC(clk, dat, rst);    
LiquidCrystal_I2C lcd(0x27,20,4);




//--------- FUNÇÕES ------------


void onCommand(){
  digitalWrite(reservatorioSensor, HIGH);

  Serial.print(" Status: ");

  int nivelArray[] =  {
    digitalRead(nivelAgua[0]),
    digitalRead(nivelAgua[1]), 
    digitalRead(nivelAgua[2])
    };

    if(nivelArray[0] == 1){
        Serial.println("reservatorio cheio");
   }  
    else if(nivelArray[1] == 0){
        Serial.println("reservatorio em 50%");
   } else if(nivelArray[2] == 0){
        Serial.println("REABASTERCER IMEDIATAMENTE!");
           lcd.clear();
        lcd.backlight();
        lcd.setCursor(0,2);
        lcd.print("REABASTECER");
        lcd.setCursor(1, 2);
        lcd.print("IMEDIATAMENTE");
   }
  
}
 


//-------- FUNÇÕES PRINCIPAIS -------------


void setup(){
  Serial.begin(9600);
// ajustar pinos i/o;
  for(short NivelAgua = 0; NivelAgua<niveis; NivelAgua++){
  pinMode(nivelAgua[NivelAgua], INPUT);
  Serial.print("Nível ");
  Serial.print(NivelAgua);
  Serial.println(" ajustado corretamente");
  }
  for(short pinosout = 0; pinosout<outputs; pinosout++){
    pinMode(output[pinosout], OUTPUT);
    Serial.println("Pinos Output:");
    Serial.print(pinosout);
    Serial.println("Ajustado!");
  }
   for(short pinosin = 0; pinosin<input; pinosin++){
    pinMode(input[pinosin], INPUT);
    Serial.println("Pinos Input:");
    Serial.print(pinosin);
    Serial.println("Ajustado!");
  }
  Serial.println("========================");
}



void loop(){
unsigned long previousMillis = 0;
const long interval = 3600000; // 1 hora
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    onCommand();
  }
    delay(3000);
}












