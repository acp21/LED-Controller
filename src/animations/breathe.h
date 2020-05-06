#ifndef BREATHE_H
#define BREATHE_H

#include "animation.h"

class Breathe : public Animation{

    public:
    // Brightness value to start at
    int startingBrightness;
    // Brightness value to end at
    int endingBrightness;
    // Is breathe in custom range?
    bool limited;
    // Is brightness currently increasing?
    bool up;
    // Is birghtness currently decreasing?
    bool down;

    Breathe(int startingLed_ = 0, int range_ = NUM_LEDS, int totalTime_ = 5, int cycleTime_ = 5, int hue_ = 0, bool limited_ = false, int startingBrightness_ = 0, int endingBrightness_ = 255, bool playNext = false);

    void next();
    void calculateWait();

};


#endif