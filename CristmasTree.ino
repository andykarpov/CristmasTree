
/**
* Christmas tree lights with Jingle Bells melody
*
*/

#include "pitches.h"

// melody notes
const int notes[] = {
  NOTE_B4,NOTE_B4,NOTE_B4, NOTE_B4,NOTE_B4,NOTE_B4, NOTE_B4,NOTE_D5,NOTE_G4,NOTE_A4, NOTE_B4, NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5, NOTE_C5,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4, NOTE_D5,NOTE_D5,NOTE_C5,NOTE_A4, NOTE_G4, NOTE_S,
  NOTE_D4,NOTE_B4,NOTE_A4,NOTE_G4, NOTE_D4,NOTE_D4,NOTE_D4, NOTE_D4,NOTE_B4,NOTE_A4,NOTE_G4, NOTE_E4,NOTE_E4, NOTE_E4,NOTE_C5,NOTE_B4,NOTE_A4, NOTE_FS4, NOTE_D5,NOTE_D5,NOTE_C5,NOTE_A4, NOTE_B4,    
  NOTE_D4,NOTE_B4,NOTE_A4,NOTE_G4, NOTE_D4,NOTE_D4,NOTE_D4, NOTE_D4,NOTE_B4,NOTE_A4,NOTE_G4, NOTE_E4,NOTE_E4, NOTE_E4,NOTE_C5,NOTE_B4,NOTE_A4, NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D5, NOTE_E5,NOTE_D5,NOTE_C5,NOTE_A4, NOTE_G4,NOTE_D5
};

// melody notes durations
const int durations[] = {
  250,250,500, 250,250,500, 250,250,375,125, 1000, 250,250,375,125, 250,250,250,125,125, 250,250,250,250, 1000, 1000,
  250,250,250,250, 750,125,125, 250,250,250,250, 750,250, 250,250,250,250, 1000, 250,250,250,250, 1000,
  250,250,250,250, 750,125,125, 250,250,250,250, 750,250, 250,250,250,250, 250,250,250,250, 250,250,250,250, 750,250
};

// pre-defined led states
byte ROW0      = B00000000;
byte ROW1      = B00011000;
byte ROW2      = B00100100;
byte ROW3      = B01000010;
byte ROW4      = B10000001;
byte ROW12     = B00111100;
byte ROW123    = B01111110;
byte ROW1234   = B11111111;
byte ROW234    = B11100111;
byte ROW34     = B11000011;
byte ROW23     = B01100110;

byte ROW1L     = B00010000;
byte ROW1R     = B00001000;
byte ROW2L     = B00100000;
byte ROW2R     = B00000100;
byte ROW3L     = B01000000;
byte ROW3R     = B00000010;
byte ROW4L     = B10000000;
byte ROW4R     = B00000001;

// melody lights sync
const byte lights[76] = {
  ROW12, ROW123, ROW1234, 
  ROW12, ROW123, ROW1234, 
  ROW1, ROW2, ROW3, ROW4, ROW1234,
  ROW4, ROW3, ROW2, ROW1, 
  ROW1, ROW2, ROW3, ROW4, ROW4,
  ROW34, ROW23, ROW12, ROW1,
  ROW1234, ROW0,
  
  ROW1, ROW2, ROW3, ROW4,
  ROW2, ROW2L, ROW2R,
  ROW1, ROW2, ROW3, ROW4,
  ROW2, ROW0,
  ROW4, ROW3, ROW2, ROW1,
  ROW1234,
  ROW1, ROW2, ROW3, ROW4,
  ROW1234,
  
  ROW1, ROW2, ROW3, ROW4,
  ROW2, ROW2L, ROW2R,
  ROW1, ROW2, ROW3, ROW4,
  ROW2, ROW0,
  ROW4, ROW3, ROW2, ROW1,
  ROW12, ROW23, ROW34, ROW1234,
  ROW1, ROW2, ROW3, ROW4,
  ROW12, ROW34
};

// light melody
const byte lights_rnd[34] = {
   ROW4L, ROW3L, ROW2L, ROW1L, ROW1R, ROW2R, ROW3R, ROW4R,
   ROW1234, ROW234, ROW34, ROW4, ROW0, ROW1234, ROW234, ROW34, ROW4, ROW0,
   ROW4, ROW3, ROW2, ROW1, ROW4, ROW3, ROW2, ROW1,
   ROW4L, ROW1R, ROW4R, ROW1L, ROW3L, ROW2R, ROW3R, ROW2L
};

const byte leds[8] = {0,1,2,3,4,5,6,7}; // leds connected to PORTD
const int ledCount = 8; // leds cound
const int noteCount = 76; // notes count
const int lightsRndCount = 34; // light rnd count
int buzzer = 11; // buzzer connected to digital pin 11
int btnPin = 8; // mode switch button pin
int mode = 0; // 0 - melody w sound, 1 - melody w/o sound, 2 - lights only
long lastTime = 0;
int i = 0;

void setup() {
  DDRD = B11111111;
  pinMode(buzzer, OUTPUT);
  pinMode(btnPin, INPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(btnPin, HIGH);
  lastTime = millis();
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    mode++;
    i=0;
    if (mode > 2) mode = 0;
    delay(250);
  }
  
  switch (mode) {
    case 0:
    case 1:
      PORTD = lights[i];
      if (mode == 0) { tone(buzzer, notes[i], durations[i]); }
      delay(durations[i]*1.1);
      if (mode == 0) { noTone(buzzer); } 
      
      i++;
      if (i > noteCount) {
        i=0;
      }
    break;
    case 2:
      PORTD = lights_rnd[i];
      delay(100);
      
      i++;
      if (i > lightsRndCount) {
        i=0;
      }
    break;
  }  
}
