#include "Audio.h"
#include "SD.h"
#include "FS.h"
#include "FastLED.h"
// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26
#define NUM_LEDS      100

Audio audio;
CRGB leds[NUM_LEDS];

int OA0 =4; 
int OA1 = 0;
int OA2 = 2;
int GS = 34;
int IA0 = 35; 
int IA1 = 32;
int IA2 = 33;

int LED =17;


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
 pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);
    SD.begin(SD_CS);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(15); // 0...21
 audio.connecttoFS(SD, "/sonidos/arranque.wav");
//play();
Serial.begin(115200);
   delay(1000);

}

void otraCancion(int num){
   
  switch (num){
        case 0:
              audio.connecttoFS(SD, "sonidos/prueba/sonido0.wav");
              Serial.println("**********start a new sound************");
        case 1:
              audio.connecttoFS(SD, "sonidos/prueba/sonido1.wav");
              Serial.println("**********start a new sound************");
        case 2:
              audio.connecttoFS(SD, "sonidos/prueba/sonido2.wav");
              Serial.println("**********start a new sound************");
        case 3:
              audio.connecttoFS(SD, "sonidos/prueba/sonido3.wav");
              Serial.println("**********start a new sound************");
        case 4:
              audio.connecttoFS(SD, "sonidos/prueba/sonido4.wav");
              Serial.println("**********start a new sound************");
        case 5:
              audio.connecttoFS(SD, "sonidos/prueba/sonido5.wav");
              Serial.println("**********start a new sound************");
        case 6:
              audio.connecttoFS(SD, "sonidos/prueba/sonido6.wav");
              Serial.println("**********start a new sound************");
        case 7:
              audio.connecttoFS(SD, "sonidos/prueba/sonido7.wav");
              Serial.println("**********start a new sound************");
        case 8:
              audio.connecttoFS(SD, "sonidos/prueba/sonido8.wav");
              Serial.println("**********start a new sound************");
        case 9:
              audio.connecttoFS(SD, "sonidos/prueba/sonido9.wav");
              Serial.println("**********start a new sound************");
        case 10:
              audio.connecttoFS(SD, "sonidos/prueba/sonido10.wav");
              Serial.println("**********start a new sound************");
        case 11:
              audio.connecttoFS(SD, "sonidos/prueba/sonido11.wav");
              Serial.println("**********start a new sound************");
        case 12:
              audio.connecttoFS(SD, "sonidos/prueba/sonido12.wav");
              Serial.println("**********start a new sound************");
        case 13:
              audio.connecttoFS(SD, "sonidos/prueba/sonido13.wav");
              Serial.println("**********start a new sound************");
        case 14:
              audio.connecttoFS(SD, "sonidos/prueba/sonido14.wav");
              Serial.println("**********start a new sound************");
        case 15:
              audio.connecttoFS(SD, "sonidos/prueba/sonido15.wav");
              Serial.println("**********start a new sound************");
        default:
              Serial.println("*********ERROR***********");
  }
        
    
}

void loop() {
   audio.loop();
switch(row){
  case 0:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
  case 1:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, LOW);
  case 2:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
  case 3:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, LOW);
  case 4:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
  case 5:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, LOW);
  digitalWrite(OA2, HIGH);
  case 6:
  digitalWrite(OA0, LOW);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
  case 7:
  digitalWrite(OA0, HIGH);
  digitalWrite(OA1, HIGH);
  digitalWrite(OA2, HIGH);
  default:
  break;
  
  
}


   if(digitalRead(GS)==1){
    leds[bottom] = CRGB::Black; FastLED.show();
 if( digitalRead(GS)==0){
    col= digitalRead(IA0)+(2*digitalRead(IA1))+(4*digitalRead(IA2));
 bottom = (row*8)+col;
   leds[bottom] = CRGB::Blue; FastLED.show();
   otraCancion(bottom);
 
}}
row++;
  if(row==8){
    row=0;
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
