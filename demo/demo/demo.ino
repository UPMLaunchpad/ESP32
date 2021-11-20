#include "BluetoothSerial.h"
#include "FastLED.h"
#include "math.h"

#define NUM_LEDS 65
int confLed[NUM_LEDS][20];
int  launchpad[8][8] = {{0,1,2,3,4,5,6,7},{15,14,13,12,11,10,9,8},{16,17,18,19,20,21,22,23},{31,30,29,28,27,26,25,24},{32,33,34,35,36,37,38,39},{47,46,45,44,43,42,41,40},{48,49,50,51,52,53,54,55},{63,62,61,60,59,58,57,56}};
CRGB leds[NUM_LEDS];
int numLed[64] = {0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8, 16, 17, 18, 19, 20, 21, 22, 23, 31, 30, 29, 28, 27, 26, 25, 26, 32, 33, 34, 35, 36, 37, 38, 39, 47, 46, 45, 44, 43, 42, 41, 40, 48, 49, 50, 51, 52, 53, 54, 55, 63, 62, 61, 60, 59, 58, 57, 56};

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
     if(bte=='-'){
      break;
    }
    Serial.write(bte);
    confLed[led][cnf]=(confLed[led][cnf]*(10))+(bte - '0');
    bte = SerialBT.read();
    if (bte ==';'){
    bte=',';
    cnf=20;
    }
  }
  
  }
 
  
}
Serial.printf("cargado");
}
  
}



void iniciarConfDemo(){
 

  char bte;
  int it;
  int led;
  int cnf;
  for(led=0;led<NUM_LEDS;led++){
  
     confLed[led][0]=numLed[NUM_LEDS];
     confLed[led][1]=0;
     confLed[led][2]=random(3);
    confLed[led][3]=random(255);
    confLed[led][3]=random(100);
    confLed[led][3]=random(100);
  
    }
    
    
    
   confLed[11][0]=12;
     confLed[11][1]=0;
     confLed[11][2]=0;
    confLed[11][3]=255;
    confLed[11][4]=99;
    confLed[11][5]=52;
  
     confLed[12][0]=11;
     confLed[12][1]=0;
     confLed[12][2]=1;
    confLed[12][3]=255;
    confLed[12][4]=99;
    confLed[12][5]=52;
 confLed[10][0]=13;
     confLed[10][1]=0;
     confLed[10][2]=2;
      confLed[9][0]=14;
     confLed[9][1]=0;
     confLed[9][2]=3;
  

Serial.printf("cargado");
}
  

void efectoCuadrado(int fila, int columna){
  int x,y;
  for (x=fila-1;x<fila+2;x++){
    for(y=columna-1;y<columna+2;y++){
      if (x<0||x>7||y<0||y>7){
        encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
      }else{
        // encenderLed(launchpad[x][y],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
         leds[launchpad[x][y]] = CRGB::Red; FastLED.show();
      }
    }
  }
 
 
  
}



 void efectoCruz(int fila, int columna){
  int x;
  for(x=0;x<8;x++){
     //encenderLed(launchpad[x][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
        leds[launchpad[x][columna]] = CRGB::Green; FastLED.show();
     //encenderLed(launchpad[fila][x],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
   leds[launchpad[fila][x]] = CRGB::Green; FastLED.show();}
 
  
}
  


 void efectoCruzProgresivo(int fila, int columna){
int i,turnos;
//encenderLed(confLed[(fila*8)+columna][0],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
 leds[confLed[(fila*8)+columna][0]] = CRGB::Blue; FastLED.show();

turnos=max(max(7-fila,7-columna),max(fila,columna));

for(i=0;i<turnos+1;i++){
    if(columna-i<0){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       leds[launchpad[fila][columna-i]] = CRGB::Blue; FastLED.show();
      // encenderLed(launchpad[fila][columna-i],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
      if(columna+i>7){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       leds[launchpad[fila][columna+i]] = CRGB::Blue; FastLED.show();
      // encenderLed(launchpad[fila][columna+i],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
    if(fila-i<0){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
       leds[launchpad[fila-i][columna]] = CRGB::Blue; FastLED.show();
     //   encenderLed(launchpad[fila-i][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }
      if(fila+i>7){
       encenderLed(64,confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    }else{
      leds[launchpad[fila+i][columna]] = CRGB::Blue; FastLED.show();
      // encenderLed(launchpad[fila+i][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
    } 
delay(500);       
      
      
}
  
  
}

 void encenderLed(int boton,int HSL1,int HSL2,int HSL3){

    //leds[boton] = CHSV(HSL1,HSL2,HSL3); FastLED.show();
 

    
      leds[boton] = CRGB::Green; FastLED.show();
      
      
      
      
     
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
     iniciarConfDemo();   

}


void loop() {
 // leds[0] = CRGB::Green; FastLED.show();
  //iniciarConf();
  
  row=random(7);
  col=random(7);
configurarEfecto(1,3);
delay(1000);
apagarLeds();
configurarEfecto(1,4);
delay(1000);
  apagarLeds();
configurarEfecto(1,2);
delay(1000);
  apagarLeds();
configurarEfecto(1,1);
  //configurarEfecto(row,col);
  delay(1000);
  apagarLeds();
 

}
