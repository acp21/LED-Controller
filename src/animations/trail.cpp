
#include "trail.h"


CRGBArray<120> myLedArr;

Trail::Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_, int jump_){
    pixelWidth = pixelWidth_;
    totalTime = totalTime_ * 1000;
    startingLed = startingLed_;
    range = range_;
    hue = hue_;
    currentPixel = startingLed_;
    prevStep = millis();
    jump = jump_;

    calculateWait();
}

void Trail::next(){
    if(millis() - prevStep >= wait){
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Blue;
        FastLED.show();
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Black;
        currentPixel += jump;
        // If statement prevents from referencing led that does not exist
        // Change static 120 to NUM_LEDS sometime
        if(currentPixel >= 120 - pixelWidth){
            currentPixel = startingLed;
        }
        Serial.println(currentPixel);
        prevStep = millis();
    }
}

void Trail::calculateWait(){
   wait = totalTime / range;
}