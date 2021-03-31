//a colocar nas livrarias
#include <Hx711.h>

//a colocar na inicializacao de variaveis 
const int PRESSURE_OUT = A3; // Pino DT
const int PRESSURE_SCK = A4; // Pino SCK

//a colocar no setup inicial no codigo da dock
void setup_pressure(){
  pinMode(PRESSURE_SCK, OUTPUT);
  pinMode(PRESSURE_OUT, INPUT);
  // reseta o HX711
  digitalWrite(PRESSURE_SCK, 1);
  delay (200);
  digitalWrite(PRESSURE_SCK, LOW);
}

//float conversao( uint8_t PRESSURE_SCK, uint8_t PRESSURE_OUT){ //se for num ficheiro separado

float read_pressure(uint8_t PRESSURE_SCK, uint8_t PRESSURE_OUT){ //no main do codigo da dock
  unsigned long PRESSURE_DATA = 0;
  digitalWrite(PRESSURE_SCK, LOW);
  
  while (digitalRead(PRESSURE_OUT)==1) ;
  
  for (int i=0; i<24; i++){
    digitalWrite(PRESSURE_SCK, HIGH);
    PRESSURE_DATA = PRESSURE_DATA<<1;
    digitalWrite(PRESSURE_SCK, LOW);
    if(digitalRead(PRESSURE_OUT) == 1) PRESSURE_DATA++;
  }
  digitalWrite(PRESSURE_SCK, HIGH);
  digitalWrite(PRESSURE_SCK, LOW);
  
  PRESSURE_DATA ^= 0x00800000;
  return PRESSURE_DATA;
}