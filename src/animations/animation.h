#ifndef ANIMATION_H
#define ANIMATION_H

#include <ArduinoJson.h>
#include <FastLED.h>
#include "pattern.h"

#define NUM_LEDS 120


class Animation{
    // Animation is an abstract class that will be a superclass for individual animation types
    public:
    int numLeds = NUM_LEDS;
    int category; // Type of animation
    int totalTime; // Total time animation plays
    int cycleTime;   // Time it takes to do one animation cycle
    int timeStarted; // Time animation started
    int startingLed; // First led in strip to play animation
    int range;       // Sequential range of all leds to play animation
    int hue;         // Hue to play animation at 
    int wait;        // Time inbetween each individual animation step
    bool current;    // Boolean marking if particular animation is currently being played
    bool completed;  // True if this animation is already completed and should not be run anymore
    bool playNext;   // Boolean marking that next animation should play simultaneously with this one
    int prevStep;    // Time of previous step
    Animation * nextAnim; // Pointer to next animation in the list

    // Each animation has same forward() function, it does things that all animations need to check
    // This could include checking if the current bool is true or not or if the animation has been completed
    void forward();

    // finish() will be used to set things such as completed bool to true
    void finish();
    // Each animation will have it's own overloaded next() function
    // Calling next() will check the current state of the animation continue it
    // This is done to avoid for loops so multiple animations can be run at one time
    void next();

    // Decode json file to get data for animation construction
    // THIS IS SUBJECT TO CHANGE
    void decodeJson();

    // This will be used to set the pointer to the next animation in the linked list
    void setNext();

    // Calculates amount of time in between each step of animation
    void calculateWait();
};

#endif