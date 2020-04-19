
#include "trail.h"


CRGBArray<120> myLedArr;

Trail::Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_){
    pixelWidth = pixelWidth_;
    totalTime = totalTime_;
    startingLed = startingLed_;
    range = range_;
    hue = hue_;
    currentPixel = startingLed_;
    prevStep = millis();

    calculateWait();
}

void Trail::next(){

    wait = 1000;
    if(millis() - prevStep >= wait){
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Blue;
        FastLED.show();
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Black;
        currentPixel++;
        prevStep = millis();
    }
}

void Trail::calculateWait(){
   wait = totalTime / range;
}