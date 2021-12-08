

#include "BluetoothSerial.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"
#include "FastLED.h"
#include "math.h"
// Digital I/O used
#define GS            35
#define IA1           36 
#define IA2           39
#define IA0           34
#define OA0           22 
#define OA1           13
#define OA2           12
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26
#define NUM_LEDS 65
int confLed[NUM_LEDS][20];
int  launchpad[8][8] = {{0,1,2,3,4,5,6,7},{15,14,13,12,11,10,9,8},{16,17,18,19,20,21,22,23},{31,30,29,28,27,26,25,24},{32,33,34,35,36,37,38,39},{47,46,45,44,43,42,41,40},{48,49,50,51,52,53,54,55},{63,62,61,60,59,58,57,56}};
CRGB leds[NUM_LEDS];

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Audio audio;
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

void searchButton(){
 switch(row){
    case 0:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
    break;
  case 1:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
    break;
  case 2:
 digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
    break;
  case 3:
 digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
    break;
  case 4:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
    break;
  case 5:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
    break;
  case 6:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
    break;
  case 7:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
    break;
  default:
    Serial.printf("Error");
    break;
}
  }

boolean bluetooth(){
  boolean cargado = false;
  char bte;
  if (SerialBT.available()) {
  File conf = SD.open("/configuraciones/configuracion.txt",FILE_WRITE);
  bte = SerialBT.read();
    while(bte != '-'){
      conf.write(bte);
      bte = SerialBT.read();
        if(bte==';'){
          conf.write(bte);
          conf.write('\n');
          bte = SerialBT.read();
    }
  }
  conf.close();
  cargado = true;
}
return cargado;
}

void cargarConfg(String path){
  File confg = SD.open(path);
  int led;
  int cnf;
  char bte;
 while (confg.available()){
  for(led=0;led<NUM_LEDS;led++){
    for(cnf=0;cnf<20;cnf++){
    bte = confg.read(); 
     while(bte!=','){
    confLed[led][cnf]= (confLed[led][cnf]*(10))+(bte - '0');
    bte = confg.read(); 
    if (bte ==';'){
    bte=',';
    cnf=20;
    }  
  }
    }
    confg.close();
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
  for(x=0;x<8;x++){
     encenderLed(launchpad[x][columna],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
     encenderLed(launchpad[fila][x],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);
  } 
}
 
void efectoCruzProgresivo(int fila, int columna){
  int i,turnos;
  encenderLed(confLed[(fila*8)+columna][0],confLed[(fila*8)+columna][3],confLed[(fila*8)+columna][4],confLed[(fila*8)+columna][5]);


  turnos=max(max(7-fila,7-columna),max(fila,columna));

  for(i=0;i<turnos+1;i++){
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
  
void setup(){
   SerialBT.begin("UPMLaunchpad");
   FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
   pinMode(GS, INPUT);
   pinMode(OA0, OUTPUT);
   pinMode(OA1, OUTPUT);
   pinMode(OA2, OUTPUT);
   pinMode(IA0,INPUT);
   pinMode(IA1,INPUT);
   pinMode(IA2,INPUT);
   digitalWrite(OA0, LOW);
   digitalWrite(OA1, LOW);
   digitalWrite(OA2, LOW);
   apagarLeds();
   inicializarConfig();
   pinMode(SD_CS, OUTPUT);
   digitalWrite(SD_CS, HIGH);
   SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
   Serial.begin(115200);
   delay(1500);
   SD.begin(SD_CS);
   audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
   audio.setVolume(10); // 0...21
   audio.connecttoFS(SD, "/sonidos/arranque.wav");
   cargarConfg("/configuraciones/configuracion.txt");
  

}




void loop(){  
  if(bluetooth()){
    cargarConfg("/configuraciones/configuracion.txt");
    }
  searchButton();
  audio.loop();
 if(digitalRead(GS)==LOW){
    col= digitalRead(IA0)+(2*digitalRead(IA1))+(4*digitalRead(IA2));
    configurarEfecto(row,col);
    audio.stopSong();
    play(confLed[(row*8)+col][3]);
    apagarLeds();
  }
  row++;
  if(row==8){
    row=0;
  } 
}

void play(int sonido){
 switch(sonido){
  case 0:
    audio.connecttoFS(SD, "/sonidos/sonido0.wav");
  //  music_info.runtime = audio.getAudioCurrentTime();
    //music_info.length = audio.getAudioFileDuration();
   // music_info.volume = audio.getVolume();
    //music_info.status = 1;
    Serial.println("**********start a new sound************");
    break;
  case 1:
    audio.connecttoFS(SD, "/sonidos/sonido1.wav");
  //  music_info.runtime = audio.getAudioCurrentTime();
    //music_info.length = audio.getAudioFileDuration();
   // music_info.volume = audio.getVolume();
    //music_info.status = 1;
    Serial.println("**********start a new sound************");
    break;
  case 2:
    audio.connecttoFS(SD, "/sonidos/sonido2.wav");
  //  music_info.runtime = audio.getAudioCurrentTime();
    //music_info.length = audio.getAudioFileDuration();
   // music_info.volume = audio.getVolume();
    //music_info.status = 1;
    Serial.println("**********start a new sound************");  
    break;
  default:
    break;


  
 }
   
}



void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
