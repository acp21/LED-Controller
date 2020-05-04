#ifndef FADE_H
#define FADE_H

#include "animation.h"

// Fade is animation that will slowly fade through all colors
class Fade : public Animation{

    public:

    Fade(int startingLed_ = 0, int range_ = NUM_LEDS, int totalTime_ = 5, int cycleTime_ = 5, int brightness = 255, bool playNext_ = false);

    void next();
    void calculateWait();
    
};

#endif