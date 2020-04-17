#ifndef ANIMATION_H
#define ANIMATION_H

#include <ArduinoJson.h>
#include <FastLED.h>

#define NUM_LEDS 120


class Animation{
    // Animation is an abstract class that will be a superclass for individual animation types
    public:
    int numLeds = NUM_LEDS;
    int category;
    int totalTime;
    int startingLed;
    int range;
    int hue;
    int wait;
    bool current;
    int prevStep;
    Animation * nextAnim;
    CRGBArray<NUM_LEDS> leds;
    // Other stuff

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