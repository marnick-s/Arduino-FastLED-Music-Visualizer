#ifndef GLOBALS_H
#define GLOBALS_H

#include <FastLED.h>

// LED LIGHTING SETUP
#define LED_PIN     6
#define NUM_LEDS    120
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 480

// AUDIO INPUT SETUP
int strobe = 4;
int reset = 5;
int audio1 = A0;
int audio2 = A1;
int left[7];
int right[7];
int band;
int audio_input = 0;
int freq = 7;
int brightness = 255;

// STANDARD VISUALIZER VARIABLES
int midway = NUM_LEDS / 2; // CENTER MARK FROM DOUBLE LEVEL VISUALIZER
int loop_max = 0;
int k = 255; // COLOR WHEEL POSITION
int decay = 0; // HOW MANY MS BEFORE ONE LIGHT DECAY
int decay_check = 0;
long pre_react = 0; // NEW SPIKE CONVERSION
long react = 0; // NUMBER OF LEDs BEING LIT
long post_react = 0; // OLD SPIKE CONVERSION

// RAINBOW WAVE SETTINGS
int wheel_speed = 2;

int sensitivity = 4; // SENSITIVITY TO MUSIC / AMOUNT OF LEDS LIT UP

#endif // GLOBALS_H