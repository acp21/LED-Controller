#include "trail.h"

Trail::Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_, CRGBArray<NUM_LEDS> leds_){
    pixelWidth = pixelWidth_;
    totalTime = totalTime_;
    startingLed = startingLed_;
    range = range_;
    hue = hue_;
    currentPixel = startingLed_;
    prevStep = millis();
    CRGBArray<NUM_LEDS> leds = leds_;

    calculateWait();
}

void Trail::next(){
    if(millis() - prevStep >= wait){
        leds(currentPixel + 1, currentPixel + range) = CRGB::Red;
        FastLED.show();
        leds[currentPixel] = CRGB::Black;
        currentPixel++;
        Serial.println("Ran trail.next");
    }
}

void Trail::calculateWait(){
   wait = totalTime / range;
}