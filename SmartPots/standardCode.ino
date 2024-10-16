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
 const short input[] = {};


unsigned const short clk;
unsigned const short dat;
unsigned const short rst;



// --------- OBJECTS ----------- //

virtuabotixRTC   myRTC(clk, dat, rst);    
LiquidCrystal_I2C lcd(0x27,20,4);




//--------- FUNÇÕES ------------


void onCommand(){
  digitalWrite(reservatorioSensor, HIGH);
  delay(5000);

  Serial.print(" Status: ");
  int readNivel = (digitalRead(nivelAgua[1,2,3]));
  Serial.println(readNivel);
  delay(1000);
  digitalWrite(reservatorioSensor, LOW);
  if(readNivel == '001'){

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
  int timer = 3600000;
  delay(timer);
  onCommand();
  delay(3000);
}












