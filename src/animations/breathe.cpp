#include "breathe.h"

Breathe::Breathe(int startingLed_, int range_, int totalTime_, int cycleTime_, int hue_, bool limited_, int startingBrightness_, int endingBrightness_, bool playNext_){
    startingLed = startingLed_;
    range = range_;
    totalTime = totalTime_ * 1000;
    cycleTime = cycleTime_ * 1000;
    hue = hue_;
    playNext = playNext_;
    startingBrightness = startingBrightness_;
    endingBrightness = endingBrightness_;
    brightness = startingBrightness;
    up = true;
    down = false;
    

    calculateWait();

}

void Breathe::next(){
    Animation::first();
    if(millis() - prevStep >= wait && !completed){
        ledArr(startingLed, range) = CHSV(hue, 255, brightness);
        if(up){
            brightness++;
            if(brightness >= endingBrightness){
                up = false;
                down = true;
            }
        }
        else if(down){
            brightness--;
            if(brightness <= startingBrightness){
                up = true;
                down = false;
            }
        }
        Serial.println(brightness);
        FastLED.show();
        prevStep = millis();
        Animation::finish();
    }
}

void Breathe::calculateWait(){
    wait = cycleTime / ((endingBrightness - startingBrightness) * 2);
}