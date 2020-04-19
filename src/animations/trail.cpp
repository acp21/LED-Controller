
#include "trail.h"


CRGBArray<120> myLedArr;

Trail::Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_, int jump_, int brightness_, bool fade_, int fadeTime_){
    pixelWidth = pixelWidth_;
    totalTime = totalTime_ * 1000;
    startingLed = startingLed_;
    range = range_;
    hue = hue_;
    currentPixel = startingLed_;
    prevStep = millis();
    jump = jump_;
    brightness = brightness_;
    fade = fade_;
    fadeTime = fadeTime_;

    calculateWait();
}

void Trail::next(){
    if(millis() - prevStep >= wait){
        myLedArr(currentPixel, currentPixel + pixelWidth) = CHSV(hue, 255, brightness);
        FastLED.show();
        // If fade == true, fade out, else, turn off immediately
        // Fade out currently not working
        if(fade){
            myLedArr[currentPixel].fadeToBlackBy(fadeTime);
        }
        else{
            myLedArr(currentPixel, currentPixel + pixelWidth) = CRGB::Black;
        }
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