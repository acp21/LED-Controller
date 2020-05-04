#include "fade.h"

// CRGBArray<120> ledArr; // Refrence to extern CRGBArray

Fade::Fade(int startingLed_, int range_, int totalTime_, int cycleTime_, int brightness_, bool playNext){
    startingLed = startingLed_;
    range = range_;
    totalTime = totalTime_ * 1000;
    cycleTime = cycleTime_ * 1000;
    playNext = playNext;
    brightness = brightness_;

    calculateWait();
};

void Fade::next(){
    Animation::first();
    if(millis() - prevStep >= wait && !completed){
        ledArr(startingLed, range) = CHSV(hue, 255, brightness);
        FastLED.show();
        hue++;
        prevStep = millis();
        Animation::finish();  
    }
}

void Fade::calculateWait(){
    wait = cycleTime / 255;
}