#include "BluetoothSerial.h"
#include "FastLED.h"
#include "math.h"

#define NUM_LEDS 65
int confLed[NUM_LEDS][20];
int  launchpad[8][8] = {{0,1,2,3,4,5,6,7},{15,14,13,12,11,10,9,8},{16,17,18,19,20,21,22,23},{31,30,29,28,27,26,25,24},{32,33,34,35,36,37,38,39},{47,46,45,44,43,42,41,40},{48,49,50,51,52,53,54,55},{63,62,61,60,59,58,57,56}};
CRGB leds[NUM_LEDS];

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int row= 0;
int col =0;
void apagarLeds(){
  
  for(int x=0;x<NUM_LEDS;x++){
    leds[x] = CRGB::Black; FastLED.show();
  }
}

void inicializarConfig(){
  int x,y;
  for(x=0;x<NUM_LEDS;x++){
    for(y=0;y<20;y++)
    confLed[x][y]=0;
  }
}
void iniciarConf(){
if(SerialBT.available()){
  char bte;
  int it;
  int led;
  int cnf;
  for(led=0;led<NUM_LEDS;led++){
  for(cnf=0;cnf<20;cnf++){
    bte = SerialBT.read();
  while(bte!=','){
    confLed[led][cnf]=(confLed[led][cnf]*(10))+(bte - '0');
    bte = SerialBT.read();
    if (bte ==';'){
    bte=',';
    cnf=20;
    }
  }
  
  }
 
  
}
}
  
}

void efectoCuadrado(int fila, int columna){
  int x,y;
  for (x=fila-1;x<fila+2;x++){
    for(y=columna-1;y<columna+2;y++){
      if (x<0||x>7||y<0||y>7){
        encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
      }else{
         encenderLed(launchpad[x][y],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
      }
    }
  }
 
 
  
}



 void efectoCruz(int fila, int columna){
  int x;
  for(x=0;x<7;x++){
     encenderLed(launchpad[x][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
     encenderLed(launchpad[fila][x],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
  }
 
  
}
  


 void efectoCruzProgresivo(int fila, int columna){
int i,turnos;
encenderLed(confLed[(fila*8)+columna][0],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);


turnos=max(max(7-fila,7-columna),max(fila,columna));

for(i=0;i<turnos;i++){
    if(columna-i<0){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       encenderLed(launchpad[fila][columna-i],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
      if(columna+i>7){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       encenderLed(launchpad[fila][columna+i],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
    if(fila-i<0){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
        encenderLed(launchpad[fila-i][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
      if(fila+i>7){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       encenderLed(launchpad[fila+i][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    } 
delay(500);       
      
      
}
  
  
}

 void encenderLed(int boton,int HSL1,int HSL2,int HSL3){

    leds[boton] = CHSV(HSL1,HSL2,HSL3); FastLED.show();
}
 void configurarEfecto(int fila, int columna){

 switch(confLed[(fila*8)+columna][2]){
  case 1:
        efectoCuadrado(fila,columna);
        break;
  case 2:
        efectoCruz(fila,columna);
        break;
  case 3:
        efectoCruzProgresivo(fila,columna);
        break;
  default:
       encenderLed(confLed[(fila*8)+columna][0],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
        break;
 
  
 }
  
}





void setup() {
  SerialBT.begin("UPMLaunchpad");
   FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
  apagarLeds();
 inicializarConfig();

 Serial.begin(115200);
    delay(1500);
    

}


void loop() {
  iniciarConf();
  row=random(7);
  col=random(7);

  configurarEfecto(row,col);
  delay(1000);
  apagarLeds();

}
