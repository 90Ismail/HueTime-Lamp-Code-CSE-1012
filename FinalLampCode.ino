/*
  Created by: Ismail Yusuf, Hamza Sigale, Yogitha Rajan Babu & Emelia Sarvela 
  
  Project Contributors and Acknowledgments

  - Tetris Theme Code:
    Robson Couto  
    Original code: https://github.com/robsoncouto/arduino-songs/blob/master/tetris/tetris.ino

  - Grove RGB LCD with Backlight:
    Seeed Studio  
    Documentation: https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/

  - NeoPixel LED Strip:
    Adafruit NeoPixel  
    Product: https://www.adafruit.com/product/1426

  - Real-Time Clock Module:
    Adafruit PCF8523 RTC Breakout Board  
    Product: https://www.adafruit.com/product/3295

  - Temperature Sensor:
    Adafruit TMP36  
    Overview: https://learn.adafruit.com/tmp36-temperature-sensor/overview

  - Course Code and Instructional Support:
    Portions of the code were adapted from Microcontrollers 1–2 and Sensors 1–2 labs in:
    CSE 1012 - University of Minnesota, Spring 2025  
    Section 001 Professors: Lauren Linderman and David Orser  
    TA: Kialie Malone  
    SolidWorks Instruction Support: Professors Lauren Linderman, David Orser, and TA Kialie Malone

  - Special Thanks:
    ECE Department at the University of Minnesota Twin Cities  
    For assistance with NeoPixel troubleshooting and soldering support.

  -ChatGPT 4.0 by OpenAI was used to help debug when the LCD and RTC wouldn't work, it helped me realize 
   I didn't connect the SCL and SDA pins properly. - April 9th 2025
*/

//Libaries needed to run the program:

#include <NeoPixelConnect.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "RTClib.h"

//Code to play tetris theme: 

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 140;
int buzzer = 18;

int melody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,

  REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5,2, NOTE_C5,2,
  NOTE_D5,2, NOTE_B4,2,
  NOTE_C5,2, NOTE_A4,2,
  NOTE_B4,1,

  NOTE_E5,2, NOTE_C5,2,
  NOTE_D5,2, NOTE_B4,2,
  NOTE_C5,4, NOTE_E5,4, NOTE_A5,2,
  NOTE_GS5,1,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,

  REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  REST,8, NOTE_E5, 4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  REST,8, NOTE_B4, 4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  REST,8, NOTE_C5, 4,  NOTE_A4,8,  NOTE_A4,4, REST, 4,

};

//Intializing melody variables (index, last note, current note & playing or not & total notes)
int noteIndex = 0; 
unsigned long lastNoteTime = 0;
unsigned long noteDurationMs = 0;
bool isNotePlaying = false;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

//Intialzing the LCD Timing

unsigned long lastLCDUpdate = 0; //LCD update
const int lcdUpdateInterval = 500; //LCD update timing

//Timing for the notes
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

//Hardware Setup

NeoPixelConnect p(19, 8);     //Neopixel LED set to Pin 19
TwoWire myWire(i2c0, 16, 17); //I2C pins, 16 & 17 are hardcoded 
rgb_lcd lcd;                  //LCD display object
RTC_PCF8523 rtc;              //Real Time Clock object
int sensorPin = A1;           //Temperature pin set to A1

//Color brightness levels

const int colorR = 10, colorG = 20, colorB = 20;

//Sets color to RGB Backlit Display
void Backlight(uint8_t r, uint8_t g, uint8_t b) {
  // Initialize the RGB controller first
  
  //Comnmunication with I2C
  myWire.beginTransmission(0x30);
  myWire.write(0x00);  // MODE1 register
  myWire.write(0x00);  // Normal operation mode
  myWire.endTransmission();
  
  //set the RGB values
  myWire.beginTransmission(0x30);  // Set red
  myWire.write(1);
  myWire.write(r);
  myWire.endTransmission();

  myWire.beginTransmission(0x30);  // Set green
  myWire.write(2);
  myWire.write(g);
  myWire.endTransmission();

  myWire.beginTransmission(0x30);  // Set blue
  myWire.write(3);
  myWire.write(b);
  myWire.endTransmission();
}


void setup () {
  // Set I2C pins manually
  Wire.setSDA(16);  // GP16 = SDA
  Wire.setSCL(17);  // GP17 = SCL
  Wire.begin();

  // Initialize Hardware
  pinMode(buzzer, OUTPUT);
  Serial.begin(57600); // Serial communication
  delay(2000);         // Serial delay

  // Initialize NeoPixel
  p.neoPixelInit(19, 8);

  // Check if RTC is working
  if (!rtc.begin(&myWire)) {
    Serial.println("RTC not found");
    while (1); // freeze if RTC not found
  }

  // --- Force RTC time update once ---
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // -----------------------------------

  // Uses computer location to track time
  if (!rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.start();

  // Initialize the LCD and print if the RTC is working
  lcd.begin(16, 2, LCD_5x8DOTS, myWire);
  lcd.noBlinkLED();
  lcd.clear();
  lcd.print("RTC ready!");
  Backlight(255, 0, 0); // test red
  delay(2000);
}

// Animate NeoPixel wave animation: current LED index, direction, last update time, and delay between steps

int ledIndex = 0;
bool goingUp = true;
unsigned long lastWaveUpdate = 0;
const int waveDelay = 75;

//A moving gradient led animation to light up the lamp
void show_wave_gradient_step(uint8_t baseR, uint8_t baseG, uint8_t baseB) {
 
 //wait for update 
  if (millis() - lastWaveUpdate < waveDelay) return;

  //adjust brightness as the LED travels highe
  float factor = 0.2 + 0.8 * (1.0 - (ledIndex / 7.0));

  //Fade the color going up and turn it off as it goes down
  if (goingUp) {
    p.neoPixelSetValue(ledIndex, baseR * factor, baseG * factor, baseB * factor, false);
  } else {
    p.neoPixelSetValue(ledIndex, 0, 0, 0, false);
  }

  //Apply and save the updated position
  p.neoPixelShow();
  lastWaveUpdate = millis();

  //Update LED index and direction
  if (goingUp) {
    ledIndex++;
    if (ledIndex > 7) {
      ledIndex = 7;
      goingUp = false;
    }
  } else {
    ledIndex--;
    if (ledIndex < 0) {
      ledIndex = 0;
      goingUp = true;
    }
  }
}

//RGB values for each second in a minute(10 second intervals) **For the showcase I think 10 seconds is better but at home 10 minutes is better
void get_color_by_second(uint8_t second, uint8_t &r, uint8_t &g, uint8_t &b) {
  if (second < 10) {
    // 00–09 seconds: Red-Pink
    r = 255; g = 0; b = 64;
  } else if (second < 20) {
    // 10–19 seconds: Orange
    r = 255; g = 100; b = 0;
  } else if (second < 30) {
    // 20–29 seconds: Yellow
    r = 255; g = 255; b = 0;
  } else if (second < 40) {
    // 30–39 seconds: Green
    r = 0; g = 255; b = 0;
  } else if (second < 50) {
    // 40–49 seconds: Blue
    r = 0; g = 0; b = 255;
  } else {
    // 50–59 seconds: Purple
    r = 128; g = 0; b = 255;
  }
}

//RGB values for each minute in an hour (10 minute intervals) **For at-home use I think 10 minutes is better but at the showcase 10 seconds is better
void get_color_by_minute(uint8_t minute, uint8_t &r, uint8_t &g, uint8_t &b) {
  if (minute < 10) {
    // 00–09 minutes: Red-Pink
    r = 255; g = 0; b = 64;
  } else if (minute < 20) {
    // 10–19 minutes: Orange
    r = 255; g = 100; b = 0;
  } else if (minute < 30) {
    // 20–29 minutes: Yellow
    r = 255; g = 255; b = 0;
  } else if (minute < 40) {
    // 30–39 minutes: Green
    r = 0; g = 255; b = 0;
  } else if (minute < 50) {
    // 40–49 minutes: Blue
    r = 0; g = 0; b = 255;
  } else {
    // 50–59 minutes: Purple
    r = 128; g = 0; b = 255;
  }
}


//handles melody playback, temperature reading, color updates, and LCD output
void loop () {
  unsigned long nowMillis = millis(); //current time

  //melody playback
  if (!isNotePlaying && nowMillis - lastNoteTime >= noteDurationMs) {
    int pitch = melody[noteIndex * 2];
    int duration = melody[noteIndex * 2 + 1];

    //calculate the note length
    if (duration > 0) {
      noteDurationMs = (wholenote) / duration;
    } else {
      noteDurationMs = ((wholenote) / abs(duration)) * 1.5;
    }

    //play the note 
    tone(buzzer, pitch, noteDurationMs * 0.9);
    isNotePlaying = true;
    lastNoteTime = nowMillis;
  } 
  //stop playing and move to next note 
  else if (isNotePlaying && nowMillis - lastNoteTime >= noteDurationMs) {
    noTone(buzzer); //stop playing 
    noteIndex++;
    isNotePlaying = false;

    //melody loop
    if (noteIndex >= notes) {
      noteIndex = 0;
    }
  }

  //Convert voltage tracked by TMP36 to a temperatue reading celsius 
  int reading = analogRead(sensorPin);
  float voltage = reading * (3.3 / 1024.0);
  float temperatureC = (voltage - 0.5) * 100;
  Serial.println(temperatureC);

  //Get current time from rtc 
  DateTime now = rtc.now();

  //track RGB values current 
  static uint8_t lastR = 255, lastG = 255, lastB = 255;

  //The rgb values using the current minute or second this can be switched if you want it change
  //every 10 seconds or 10 minutes 
  uint8_t r, g, b;
  uint8_t currentMinute = now.minute();
  uint8_t currentSecond = now.second();

  get_color_by_second(currentSecond, r, g, b); // Same for LCD + NeoPixel

  //// Only update LCD color if RGB values changed
  if (r != lastR || g != lastG || b != lastB) {
  lcd.setRGB(r, g, b);
    lastR = r;
    lastG = g;
    lastB = b;
  }

  //Change color wave with current color 
  show_wave_gradient_step(r, g, b);

  //LCD text display
  if (nowMillis - lastLCDUpdate >= lcdUpdateInterval) {
    lastLCDUpdate = nowMillis;

    //Column 1
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.year() % 100);
    lcd.print(' '); 
    lcd.print(now.hour());
    lcd.print(':');
    if (currentMinute < 10) lcd.print('0');
    lcd.print(currentMinute);

    //Column 2
    lcd.setCursor(0, 1);
    lcd.print(int(temperatureC));
    lcd.print((char)223); //degree symbol
    lcd.print("Celsius");
  }
}