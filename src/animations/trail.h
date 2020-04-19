#ifndef TRAIL_H
#define TRAIL_H

#include "animation.h"

class Trail : public Animation{
    
    public:
    int pixelWidth;
    int currentPixel;
    int wait;
    int jump; // Distance in LEDS lit leds jump after each step

    Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_, int jump_);
    void next();
    void calculateWait();

};

#endif