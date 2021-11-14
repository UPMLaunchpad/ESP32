

#include "FastLED.h"
#define NUM_LEDS 100
CRGB leds[NUM_LEDS];
int OA0 =4; 
int OA1 = 0;
int OA2 = 2;
int GS = 34;
int IA0 = 35; 
int IA1 = 32;
int IA2 = 33;

int LED =17;

///int out = 23;

int row= 0;
int col =0;
int bottom=0;   
void setup() {
  FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
  // put your setup code here, to run once:
  pinMode(OA0, OUTPUT);
  pinMode(OA1, OUTPUT);
  pinMode(OA2, OUTPUT);
  pinMode(GS, INPUT);
  pinMode(IA0,INPUT);
   pinMode(IA1,INPUT);
    pinMode(IA2,INPUT);
 // pinMode(out, OUTPUT);
Serial.begin(115200);
   delay(1000);
  
   
}

void loop() {
  delay(1000);
switch(row){
  case 0:{
     Serial.printf(" opcion: %d ",row); 
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
    break;
 }
  case 1:{
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 2:{
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 3:{
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 4:{
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 5:{
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 6:{
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
  Serial.printf(" opcion: %d ",row);
    break;}
  case 7:{
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
  Serial.printf(" opcion: %d ",row);
    break;
  }
  default:
  break;
  
  
}


   if(digitalRead(GS)==1){
    leds[bottom] = CRGB::Black; FastLED.show();
 if( digitalRead(GS)==0){
    col= digitalRead(IA0)+(2*digitalRead(IA1))+(4*digitalRead(IA2));
 bottom = (row*8)+col;
   leds[bottom] = CRGB::Blue; FastLED.show();
 
}}
row++;
  if(row==8){
    row=0;
  }

   
/*
Serial.printf(" pin 34: %d ",digitalRead(GS));
Serial.printf(" pin 35: %d ",digitalRead(IA0));
Serial.printf(" pin 32: %d ",digitalRead(IA1));
Serial.printf(" pin 33: %d ",digitalRead(IA2));
*/

    

Serial.printf(" fila: %d ",row);
 



}
