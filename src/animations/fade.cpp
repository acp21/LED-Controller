#include "fade.h"

// CRGBArray<120> ledArr; // Refrence to extern CRGBArray

Fade::Fade(int startingLed_, int range_, int totalTime_, int cycleTime_, bool playNext){
    startingLed = startingLed_;
    range = range_;
    totalTime = totalTime_;
    cycleTime = cycleTime_;
    playNext = playNext;
};

void Fade::next(){
    
}