#ifndef definitions
#define definitions

//include libaries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED 
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
extern Adafruit_SSD1306 oled;
// display menu
#define menuReaction 10
#define menuMemory 35

// LEDs
#define LED_PIN 23
#define LED_COUNT 6
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define ledThumbLeft 0
#define ledThumbRight 5

//names and pinnumbers of fixed variables for arduino nano
//button variables
#define button1 36//A0 //rot
#define button2 39//A1 //grün
#define button3 34//A2 //gelb
#define button4 35//A3 //blau
#define buttonThumbLeft 32//A7 //orange
#define buttonThumbRight 33//A6 //orange
// threshold for analog button readout
#define THRESHOLD 50
#define THRESHOLD_VIB 105 //85
#define ZERO 20

//vibration motor variables
#define vibration1 18 //rot
#define vibration2 19 //grün
#define vibration3 16 //gelb
#define vibration4 15 //blau
#define vibrationThumbLeft 5 //orange
#define vibrationThumbRight 17 //orange
#define SPEED 1023

// SDA 21
// SCL 22

// condition to go into main menu after the game is finished
extern bool gameFinished;
extern void vibrateAll();

// thumb button variables 
extern int buttonThumb;
extern int vibrationThumb;
extern int ledThumb;
extern int vibrations[];
extern int ledArray[];

//flags for button pushes
extern bool prestate1;
extern bool prestate2;
extern bool prestate3;
extern bool prestate4;
extern bool prestateThumb;

extern Adafruit_NeoPixel leds;
extern void ledOn(int led, int r = 0, int g = 150, int b = 100);
extern void ledOff();

enum Mode {vib, led, both};
extern Mode mode;

// calibrated force values
extern int getFinger1();
extern int getFinger2();
extern int getFinger3();
extern int getFinger4();
extern int getThumb();

#endif
