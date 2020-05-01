#include "animation.h"

// Each animation runs this to check if next step is needed
bool Animation::forward(){
    Serial.println("Called");
    if(completed){
        // Run this code if animation has been completed
        return false;
    }
    // If animation is not completed, call next()
    else{
        if(millis() - prevStep >= wait){
            // Serial.print("PREV");
            // Serial.println(prevStep);
            // Serial.print("WAIT");
            // Serial.print
            // Serial.println("Returning True");
            return true;
            
        }
        else{
            return false;
        }
    }
}

void Animation::finish(){
    if(millis() - timeStarted >= totalTime){
        Serial.println("Animation finished!");
        timeStarted = millis();
        completed = true;
        ledArr(startingLed, range) = CRGB::Black;
        FastLED.show();
    }
}

void Animation::first(){
    if(firstLoop){
        timeStarted = millis();
        firstLoop = false;
    }
}

// Check following link
// https://www.learncpp.com/cpp-tutorial/11-6a-calling-inherited-functions-and-overriding-behavior/
// Section adding to existing functionality

// void Animation::next(){
//     Serial.println("I shouldnt see this");
// }