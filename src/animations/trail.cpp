
#include "trail.h"


CRGBArray<120> ledArr;

Trail::Trail(int pixelWidth_, int totalTime_, int cycleTime_, int startingLed_, int range_, int hue_, int jump_, int brightness_, bool fade_, int fadeTime_){
    pixelWidth = pixelWidth_;
    totalTime = totalTime_ * 1000;
    cycleTime = cycleTime_ * 1000;
    startingLed = startingLed_;
    range = range_;
    hue = hue_;
    currentPixel = startingLed_;
    prevStep = millis();
    timeStarted = prevStep;
    jump = jump_;
    brightness = brightness_;
    fade = fade_;
    fadeTime = fadeTime_;
    firstLoop = true;

    calculateWait();
}
void Trail::next(){
    Animation::first();
    if(millis() - prevStep >= wait && !completed){
        Serial.println("Stepped");
        ledArr(currentPixel, currentPixel + pixelWidth) = CHSV(hue, 255, brightness);
        FastLED.show();
        // If fade == true, fade out, else, turn off immediately
        // Fade out currently not working
        if(fade){
            ledArr[currentPixel].fadeToBlackBy(fadeTime);
        }
        else{
            ledArr(currentPixel, currentPixel + pixelWidth) = CRGB::Black;
        }
        currentPixel += jump;
        // If statement prevents from referencing led that does not exist
        // Change static 120 to NUM_LEDS sometime
        if(currentPixel >= 120 - pixelWidth){
            currentPixel = startingLed;
        }
        // Serial.println(currentPixel);
        prevStep = millis();
        Animation::finish();
    }
}


void Trail::calculateWait(){
   wait = cycleTime / range;
}