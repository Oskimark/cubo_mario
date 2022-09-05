#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "SD.h" //Lib to read SD card
#include "TMRpcm.h" //Lib to play auido
#include "SPI.h" //SPI lib for SD card

#define SD_ChipSelectPin 4 //Chip select is pin number 4
TMRpcm music; //Lib object is named "music"

#define PIN 6
//#define PIN2 3
#define NUMPIXELS 4
//#define NUMPIXELS2 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800);

int GOLPES = 0;
int boton = 2;
long tiempo_anterior;
long diferencia;
bool encendido = false;
bool flagLuces = false;

void setup() {
Serial.begin(9600);
pinMode(boton, INPUT_PULLUP);
pixels.begin(); // This initializes the NeoPixel library.
pixels.show(); // initialize all pixels to "off"
attachInterrupt(digitalPinToInterrupt(boton), cambiaEstadoLED, RISING);

if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}
music.speakerPin = 9; //Auido out on pin 9
music.setVolume(5); // 0 to 7. Set volume level
music.quality(1); // Set 1 for 2x oversampling Set 0 for normal
}

void loop() {
  music.play("37.wav");
  rainbow(60);
  rainbow(60);
   music.play("38.wav");
  rainbow(40);
  rainbow(40);
}

void cambiaEstadoLED(){
coin();
GOLPES+=1;

if (GOLPES % 11 == 0){
  life();}
if (GOLPES % 8 == 0){
  star(); }    
}

void coin(){
  music.play("31.wav");
moneda();
//music.disable();
  }
void life(){
  music.play("30.wav");
vida();
music.disable();
  }
void star(){
  detachInterrupt(digitalPinToInterrupt(2));
  music.play("36.wav");
estrella(20);
music.disable();
attachInterrupt(digitalPinToInterrupt(boton), cambiaEstadoLED, RISING);
  }
void flag(){
  
  }


void botonLuces(){
diferencia = millis() - tiempo_anterior;
tiempo_anterior = millis();
if(diferencia > 1000){
flagLuces = true;
}}
void moneda(){
  setLeds(200,255,255,255);
  setLeds(200,0,0,0);
  setLeds(200,255,255,255);
  setLeds(200,0,0,0); 
}
void vida(){
  setLeds(100,255,255,0);
  setLeds(100,0,0,0);
  setLeds(100,255,255,0);
  setLeds(100,0,0,255); 
  setLeds(100,255,255,0);
  setLeds(100,0,0,255);
  setLeds(100,255,255,0);
  setLeds(100,0,0,255); 
}
void estrella(int wait){
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<333; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (pixels.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue)); // hue -> RGB
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
void setLeds(int tiempo, int r, int g, int b){
  for (int led = 0; led < 4 ; led++)
  {
    pixels.setPixelColor(led,   r ,  g ,  b);
  }

  pixels.show();
  delay(tiempo);
}
void apagar(){
uint16_t i, j;
for (j = 255; j > 0; j--) {
for(int i=0;i<NUMPIXELS;i++){
pixels.setPixelColor(i, pixels.Color(23,161,165));
}
pixels.setBrightness(j);
pixels.show();
delay(10);
}}
void rainbow(int wait) {
  pixels.setBrightness(255);
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 512) {
    for(int i=0; i<4; i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
}
if(flagLuces){
flagLuces = false;
cambiaEstadoLED();
}}
