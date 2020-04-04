// LED-Control
// Written by Adam Pohl

#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>


#define NUM_LEDS 120
#define DATA_PIN 14

CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2812B, 14, GRB>(leds, NUM_LEDS);
}

 void loop() {
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Blue;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(25);
      }
    }