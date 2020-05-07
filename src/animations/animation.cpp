#include "animation.h"

// Each animation runs this to check if next step is needed
// This function is currently unused
bool Animation::forward(){
    Serial.println("Called");
    if(completed){
        // Run this code if animation has been completed
        return false;
    }
    // If animation is not completed, call next()
    else{
        if(millis() - prevStep >= wait){
            return true;
        }
        else{
            return false;
        }
    }
}

// Will check if totalTime has been elapsed
// If so, darken all leds in animation range and set completed = true
void Animation::finish(){
    if(millis() - timeStarted >= totalTime){
        Serial.println("Animation finished!");
        timeStarted = millis();
        completed = true;
        ledArr(startingLed, range) = CRGB::Black;
        FastLED.show();
    }
}

// Called firs time animation is looped through to properly establish start time
void Animation::first(){
    if(firstLoop){
        Serial.println("First loop");
        timeStarted = millis();
        firstLoop = false;
    }
}

// void Animation::next(){
//     nextAnim -> next();
// }

// Check following link
// https://www.learncpp.com/cpp-tutorial/11-6a-calling-inherited-functions-and-overriding-behavior/
// Section adding to existing functionality
