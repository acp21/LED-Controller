// THIS FILE IS NOT COMPLETE

#include "sparkle.h"
#include <random>

Sparkle::Sparkle(int startingLed_, int range_, int totalTime_, float fadeTime_, float fadeTimeVariance_, float betweenTime_, float betweenTimeVariance_, int maxBrightness_, int maxBrightnessVariance_, int numPixels_, int maxPixels_){
    startingLed = startingLed_;
    range = range_;
    totalTime = totalTime_ * 1000;
    fadeTime = fadeTime_ * 1000;
    fadeTimeVariance = fadeTimeVariance_ * 1000;
    betweenTime = betweenTime_ * 1000;
    betweenTimeVariance = betweenTimeVariance_ * 1000;
    maxBrightness = maxBrightness;
    maxBrightnessVariance = maxBrightnessVariance_;
    numPixels = numPixels_;
    maxPixels = maxPixels_;
    prevBlink = millis();
    std::srand((unsigned) millis());
}

void Sparkle::next(){
    Animation::first();
    light();
    dim();

}

void Sparkle::light(){
    if(millis() - prevBlink >= wait && !completed){
        for(int i = 0; i < numPixels; i++){
            int n = (rand() % (startingLed + range - 1));
            ledArr[n] = CHSV(hue, 255, 255);
            pixelStrengths[n] = 255;
            dimWaits[n] = calculateDim();
        }
        prevBlink = millis();
    }
}

void Sparkle::dim(){
    for(int i = startingLed; i < startingLed + range; i++){
        if(pixelStrengths[i] > 0){
            pixelStrengths[i]--;
            ledArr[i] = CHSV(hue, 255, pixelStrengths[i]);
        }
    }
}

int Sparkle::calculateDim(){
    int bright = calculateBright();
    
    return 0;
}

int Sparkle::calculateBright(){
    // Generate boolean to determine if value added or subtracted
    bool positive = (rand() % 2);
    // Generate value to be added
    int variance = (rand() % maxBrightnessVariance);
    int bright;
    // If boolean == 1, add varience, else subtract
    if(positive){
        bright + variance;
    }
    else{
        bright - variance;
    }
    // Keep bright within bounds
    if(bright > 255){
        bright = 255;
    }
    else if(bright < 0){
        bright = 0;
    }

    return bright;
}