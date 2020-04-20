#include "animation.h"


void Animation::forward(){
    if(completed){
        // Run this code if animation has been completed
    }
}

void Animation::finish(){
    if(millis() - timeStarted >= totalTime){
        Serial.println("Animation finished!");
        timeStarted = millis();
    }
}