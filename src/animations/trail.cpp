// #include "main.cpp"
#include "trail.h"

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
    // myLedArr[1] = CRGB::Blue;
    // FastLED.show();
    // Serial.println("Trail");
    wait = 1000;
    if(millis() - prevStep >= wait){
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Red;
        FastLED.show();
        myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Black;
        currentPixel++;
        Serial.println("Ran trail.next");
        prevStep = millis();
    }
}

void Trail::calculateWait(){
   wait = totalTime / range;
}