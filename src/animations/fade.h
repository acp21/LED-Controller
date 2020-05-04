#ifndef FADE_H
#define FADE_H

#include "animation.h"

// Fade is animation that will slowly fade through all colors
class Fade : public Animation{

    public:
    // If true, cycle contains all colors
    bool rgb;
    // Color fade starts on: MUST BE LOWER VAL THAN endingColor
    int startingColor;
    // Color fade ends on: MUST BE HIGHER VAL THAN startingColor
    int endingColor;
    // Is hue currently increasing?
    bool up;
    // Is hue currently decreasing?
    bool down;

    Fade(int startingLed_ = 0, int range_ = NUM_LEDS, int totalTime_ = 5, int cycleTime_ = 5, int brightness = 255, bool rgb_ = true, int startingColor_ = 0, int endingColor_ = 255, bool playNext_ = false);

    void next();
    void calculateWait();
    
};

#endif